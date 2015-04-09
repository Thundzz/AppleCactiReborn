#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "../common.h"
#include "gui.h"
#include "../game/game.h"
#include "../texts.h"
#define DEFAULT_W 800
#define DEFAULT_H 600
#define FONT_SIZE 20
#define BGCOLOR 0x128f52
#define RES_PATH "../res/"
#define IMG_PATH RES_PATH "images/"
#define TILE_PATH IMG_PATH "tile/"
#define JOKER_PATH IMG_PATH "joker/"
#define FONT_PATH RES_PATH "font/font.ttf"

typedef enum{TTF, SDL} lib;

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
  SDL_Surface *screen, *board;
  struct{SDL_Surface *tile[NB_TILE_CONTENT];
    SDL_Surface *score[NB_PLAYER];
    SDL_Surface *joker[NB_JOKER];} img;
  struct{TTF_Font *font; SDL_Color color;} text;
  struct{SDL_Surface * msg; SDL_Surface *status;} info;
} gui_t;

static gui_t gui;

void gui_perror(const char * msg, lib l)
{
  fprintf(stderr, ERROR, msg, (l == TTF) ? TTF_GetError() : SDL_GetError());
}

void gui_draw_board()
{
  SDL_Rect pos;
  pos.x = pos.w = pos.y = 0;
  game_t *game = game_get();
  for(int i=0; i<BOARD_SIZE; ++i)
    {
      pos.y = 0;
      for(int j=0; j<BOARD_SIZE; ++j)
	{
	  SDL_BlitSurface(gui.img.tile[tile_get_content(&(game->board)[i][j])], NULL, gui.board, &pos);
	  pos.y += gui.img.tile[0]->h + 1;
	}
      pos.x += gui.img.tile[0]->w + 1;
    }
  SDL_BlitSurface(gui.board, NULL, gui.screen, &gui.absp.board);
}

void gui_draw()
{
  gui_draw_board();
  SDL_Flip(gui.screen);
}

void gui_compute_positions()
{
  /* todo use ratios to define every position from screen->h/w */
  int h = gui.screen->h;
  int w = gui.screen->w;
  gui.absp.msg.x = 0;
  gui.absp.msg.y = h-TTF_FontHeight(gui.text.font);
  gui.absp.msg.w = w;
  gui.absp.msg.h = TTF_FontHeight(gui.text.font);
  gui.absp.board.x = 0;
  gui.absp.board.y = 0;
  gui.absp.board.w = gui.board->w;
  gui.absp.board.h = gui.board->w;
}

int gui_init()
{
  if(SDL_Init(SDL_INIT_VIDEO) == -1)
    {
      gui_perror(SDL_INIT_FAILURE, SDL);
      return GUI_ERROR;
    }
  gui.screen = SDL_SetVideoMode(800, 600, 32, SDL_DOUBLEBUF | SDL_RESIZABLE);
  if(gui.screen == NULL)
    {
      gui_perror(SDL_INIT_FAILURE, SDL);
      return GUI_ERROR;
    }
  SDL_FillRect(gui.screen, NULL, BGCOLOR);
  char buf[256];
  for(int i =0; i < NB_TILE_CONTENT; ++i)
    {
      sprintf(buf, TILE_PATH "%d.bmp", i);
      gui.img.tile[i] = SDL_LoadBMP(buf);
      if(gui.img.tile[i] == NULL)
	{
	  gui_perror(AT_LOADING, SDL);
	  return GUI_ERROR;
	}
    }
  gui.board = SDL_CreateRGBSurface(SDL_HWSURFACE, BOARD_SIZE * (gui.img.tile[0]->w+1), BOARD_SIZE * (gui.img.tile[0]->h+1), 32, 0, 0, 0, 0);
  if(gui.board == NULL)
    {
      gui_perror(AT_LOADING, SDL);
      return GUI_ERROR;
    }
  /* to be uncommented when jokers are displayed */
  /*
  for(int i =0; i < NB_JOKER; ++i)
    {
      sprintf(buf, JOKER_PATH "%d.bmp", i);
      gui.img.joker[i] = SDL_LoadBMP(buf);
      if(gui.img.joker[i] == NULL)
	{
	  gui_perror(AT_LOADING, SDL);
	  return GUI_ERROR;
	}
     }
  */
  if(TTF_Init() == -1)
    {
      gui_perror(SDL_TTF_INIT_FAILURE, TTF);
      return GUI_ERROR;
    }
  gui.text.font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
  if(gui.text.font == NULL)
    {
      gui_perror(FONT_PATH, TTF);
      return GUI_ERROR;
    }
  gui.text.color.r = gui.text.color.g = gui.text.color.b = 0;
  gui.info.msg = gui.info.status = NULL;
  gui_compute_positions();
  gui_info(NEW_GAME);
  gui_draw();
  return GUI_OK;
}

int gui_player_uses_joker(joker_t * joker, player_id player)
{
  return GUI_OK;
}

int gui_get_move(move_t * move, player_id player)
{
  return GUI_OK;
}

/*returns a boolean. change should be considered: this blocks error handling.*/
int gui_wannaplayagain()
{
  gui_info(PLAY_AGAIN);
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
  return GUI_OK;
}

int gui_info(char *msg)
{
  if(msg != NULL)
    {
      if(gui.info.msg != NULL)
	{
	  SDL_FreeSurface(gui.info.msg);
	  SDL_FillRect(gui.screen, &gui.absp.msg, BGCOLOR);
	}
      gui.info.msg = TTF_RenderText_Solid(gui.text.font, msg, gui.text.color);
      if(gui.info.msg == NULL)
	{
	  gui_perror(RENDER_TEXT_FAILED, TTF);
	  puts(msg);
	  return GUI_ERROR;
	}
    }
  SDL_BlitSurface(gui.info.msg, NULL, gui.screen, &gui.absp.msg);
  SDL_Flip(gui.screen);
  return GUI_OK;
}

int gui_status(char *msg)
{
  return GUI_OK;
}

int gui_quit()
{
  for(int i = 0; i < NB_TILE_CONTENT; ++i)
    SDL_FreeSurface(gui.img.tile[i]);
  for(int i = 0; i < NB_TILE_CONTENT; ++i)
    SDL_FreeSurface(gui.img.joker[i]);
  if(gui.info.msg != NULL)
    SDL_FreeSurface(gui.info.msg);
  if(gui.info.msg != NULL)
    SDL_FreeSurface(gui.info.status);
  TTF_CloseFont(gui.text.font);
  TTF_Quit();
  SDL_Quit();
  return GUI_OK;
}
