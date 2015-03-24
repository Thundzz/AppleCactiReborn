#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "common.h"
#include "gui.h"
#include "game.h"


#define DEFAULT_W 800
#define DEFAULT_H 600
#define FONT_SIZE 20
#define BGCOLOR 0x128f52
#define RES_PATH "../res/"
#define IMG_PATH RES_PATH "img/"
#define SQUARE_PATH IMG_PATH "square/"
#define JOKER_PATH IMG_PATH "joker/"
#define FONT_PATH RES_PATH "font/font.ttf"



typedef struct{
  SDL_Rect board, p1, p2, status, current_player, msg;
} gui_absolute_positions_t;

typedef struct{
  SDL_Rect pcount, pjoker, info;
} gui_relative_positions_t;

typedef struct gui_s
{
  gui_absolute_positions_t absp;
  gui_relative_positions_t relp;
  SDL_Surface *screen;
  struct{SDL_Surface *square[NB_SQUARE_CONTENT];
    SDL_Surface *score[NB_PLAYER];
    SDL_Surface *joker[NB_JOKER];} img;
  struct{TTF_Font *font; SDL_Color color;} text;
  struct{SDL_Surface * msg; SDL_Surface *status;} info;
} gui_t;

static gui_t gui;

void gui_compute_positions()
{
  /* todo use ratios to define every position from screen->h/w */
  int h = gui.screen->h;
  int w = gui.screen->w;
  gui.absp.msg.x = 0;
  gui.absp.msg.y = h-TTF_FontHeight(gui.text.font);
  gui.absp.msg.w = w;
  gui.absp.msg.h = TTF_FontHeight(gui.text.font);
}

int gui_init()
{
  char buf[256];
  SDL_Init(SDL_INIT_VIDEO);
  gui.screen = SDL_SetVideoMode(800, 600, 32, SDL_DOUBLEBUF | SDL_RESIZABLE);
  SDL_FillRect(gui.screen, NULL, BGCOLOR);
  for(int i =0; i < NB_SQUARE_CONTENT; ++i)
    {
      sprintf(buf, SQUARE_PATH "%d.bmp", i);
      gui.img.square[i] = SDL_LoadBMP(buf);
    }
  for(int i =0; i < NB_JOKER; ++i)
    {
      sprintf(buf, JOKER_PATH "%d.bmp", i);
      gui.img.joker[i] = SDL_LoadBMP(buf);
    }
  TTF_Init();
  gui.text.font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
  puts(TTF_GetError());
  gui.text.color.r = gui.text.color.g = gui.text.color.b = 0;
  gui.info.msg = gui.info.status = NULL;
  gui_compute_positions();
  gui_info("New game.");
  return 0;
}

int gui_player_uses_joker(joker_t * joker)
{
  return 0;
}

int gui_get_move(move_t * move, player_id player)
{
  return 0;
}

int gui_show_move(move_log_t * mlog)
{
  return 0;
}

int gui_wannaplayagain()
{
  gui_info("Play again ? (Y/n)");
  SDL_Event event;
  for(;;)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
	{
	case SDL_QUIT:
	  return 0;
	  break;
	case SDL_KEYDOWN:
	  switch(event.key.keysym.sym)
	    {
	    case SDLK_y:
	    case SDLK_RETURN:
	      return 1;
	      break;
	    case SDLK_ESCAPE:
	    case SDLK_n:
	    case SDLK_q:
	      return 0;
	      break;
	    default:
	      break;
	    }
	}
    }
  return 0;
}

int gui_info(char *msg)
{
  if(gui.info.msg != NULL)
    {
      SDL_FreeSurface(gui.info.msg);
      SDL_FillRect(gui.screen, &gui.absp.msg, BGCOLOR);
    }
  gui.info.msg = TTF_RenderText_Solid(gui.text.font, msg, gui.text.color);
  SDL_BlitSurface(gui.info.msg, NULL, gui.screen, &gui.absp.msg);
  SDL_Flip(gui.screen);
  return 0;
}

int gui_status(char *msg)
{
  return 0;
}

int gui_quit()
{
  for(int i = 0; i < NB_SQUARE_CONTENT; ++i)
    SDL_FreeSurface(gui.img.square[i]);
  for(int i = 0; i < NB_SQUARE_CONTENT; ++i)
    SDL_FreeSurface(gui.img.joker[i]);
  if(gui.info.msg != NULL)
    SDL_FreeSurface(gui.info.msg);
  if(gui.info.msg != NULL)
    SDL_FreeSurface(gui.info.status);
  TTF_CloseFont(gui.text.font);
  TTF_Quit();
  SDL_Quit();
  return 0;
}
