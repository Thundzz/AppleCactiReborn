#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "common.h"
#include "gui.h"
#include "game.h"


#define DEFAULT_W 800
#define DEFAULT_H 600
#define FONT_SIZE 30

#define IMG_PATH "../img/"
#define SQUARE_PATH "square/"
#define JOKER_PATH "joker/"
#define FONT_PATH "font/font.ttf"

typedef struct{
  SDL_Rect board, p1, p2, status, current_player;
} gui_absolute_positions_t;

typedef struct{
  SDL_Rect pcount, pjoker, info;
} gui_relative_positions_t;

typedef struct gui_s
{
  gui_absolute_positions_t absp;
  gui_relative_positions_t relp;
  SDL_Surface *screen;
  SDL_Surface *square[NB_SQUARE_CONTENT];
  SDL_Surface *score[NB_PLAYER];
  SDL_Surface *joker[NB_JOKER];
  TTF_Font *font;
} gui_t;

void gui_compute_positions(gui_t *g)
{
  /* todo use ratios to define every position from screen->h/w */
}

gui_t * gui_init(game_t *game)
{
  char buf[256];
  gui_t *g = malloc(sizeof(gui_t));
  SDL_Init(SDL_INIT_VIDEO);
  g->screen = SDL_SetVideoMode(800, 600, 32, SDL_DOUBLEBUF | SDL_RESIZABLE);
  gui_compute_positions(g);
  for(int i =0; i < NB_SQUARE_CONTENT; ++i)
    {
      sprintf(buf, IMG_PATH SQUARE_PATH "%d.bmp", i);
      g->square[i] = SDL_LoadBMP(buf);
    }
  for(int i =0; i < NB_JOKER; ++i)
    {
      sprintf(buf, IMG_PATH JOKER_PATH "%d.bmp", i);
      g->joker[i] = SDL_LoadBMP(buf);
    }
  TTF_Init();
  g->font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
}

int gui_player_uses_joker(gui_t * g, joker_t * joker)
{
  return 0;
}

int gui_get_move(gui_t *g, move_t * move, player_id player)
{
  return 0;
}

int gui_show_move(gui_t*g, move_log_t * mlog)
{
  return 0;
}

int gui_wannaplayagain(gui_t *g)
{
  return 0;
}

int gui_info(char *msg)
{
  return 0;
}

int gui_status(char *msg)
{
  return 0;
}

int gui_quit(gui_t * g)
{
  for(int i = 0; i < NB_SQUARE_CONTENT; ++i)
    SDL_FreeSurface(g->square[i]);
  for(int i = 0; i < NB_SQUARE_CONTENT; ++i)
    SDL_FreeSurface(g->joker[i]);
  TTF_CloseFont(g->font);
  TTF_Quit();
  SDL_Quit();
  free(g);
}
