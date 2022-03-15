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

void menu(char *tabtest, SDL_Rect *rect, SDL_Renderer *renderer);
void modeRandom(char *tabtest, SDL_Rect *rect, SDL_Renderer *renderer);
void iniTab(char *tabtest, SDL_Rect *rect);
void randomInput(char *tabtest, SDL_Rect *rect, SDL_Renderer *renderer);
void showEvolution(char *tabtest, SDL_Rect *rect, SDL_Renderer *renderer);
void showGen(char *tabtest, SDL_Rect *rect, SDL_Renderer *renderer);
void tabtestGenPlusOne(char *tabtest, SDL_Rect *rect, SDL_Renderer *renderer);
int nombreVoisins(char *tabtest, int x, int y);
void showTab(char *tabtest);

#endif
