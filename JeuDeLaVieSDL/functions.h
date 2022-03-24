#ifndef functions_h
#define functions_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define COLONNES (WINDOW_WIDTH/10*2)
#define LIGNES (WINDOW_HEIGHT/10*2)
#define CELLALIVE '@'
#define CELLDEAD ' '
#define SQUARESIZE 4
#define TAUXMUT 10
#define TAUXAPO 1
#define GENMULT 1
#define RATIOYESNO 1
#define RECENTDEAD '*'
#define RECENTDEADYESNO 0

#define NBALGO 5
#define POPTOT 5
#define XGEN 60
#define YGEN 700
#define TEAMS 1
#define MODE 1


void menu(char *tab, SDL_Rect *rect, SDL_Renderer *renderer, SDL_Texture *texture, int *colors);
void gameLoop(char *tab, SDL_Rect *rect, SDL_Renderer *renderer, int gameMode, int *colors);
void iniTab(char *tab, SDL_Rect *rect);
void randomInput(char *tab, SDL_Rect *rect, SDL_Renderer *renderer, int *colors);
void showEvolution(char *tab, SDL_Rect *rect, SDL_Renderer *renderer);
void showGen(char *tab, SDL_Rect *rect, SDL_Renderer *renderer, int *colors);
void tabGenPlusOne(char *tab, SDL_Rect *rect, SDL_Renderer *renderer, int gameMode, int *colors);
int nombreVoisins(char *tab, int x, int y);
void showTab(char *tab);
void gameLoopGenetic(char *tab, SDL_Rect *rect, SDL_Renderer *renderer, int *colors);
int fitness(char *tab, int nbalg);
int relCellState(char *tab, int x, int y, int xx, int yy);
int findSquare(char *tab, int x, int y);
int find3LineVert(char *tab, int x, int y);
int find3LineHori(char *tab, int x, int y);
void iniColors(char *tab, int *colors);
int nombreColors(int *colors, int x, int y);


#endif
