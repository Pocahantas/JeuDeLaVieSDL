#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "functions.h"

void exitError(const char *message){
    SDL_Log("Erreur %s: %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

int main(int argc, char * argv[]) {
    srand((int)time(NULL));
    char *tab = NULL;
    tab = (char*)malloc(sizeof(char)*COLONNES*LIGNES);
    SDL_Rect *rect = NULL;
    rect = (SDL_Rect*)malloc(sizeof(SDL_Rect)*COLONNES*LIGNES);
    /*-------------------------------------------------------*/
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if(SDL_Init(SDL_INIT_VIDEO) != 0) exitError("Impossible d'initialiser SDL");
    window = SDL_CreateWindow("Jeu de la vie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if(window == NULL) exitError("SDL_CreateWindow");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) exitError("SDL_CreateRenderer");
    /*-------------------------------------------------------*/

    iniTab(tab, rect);
    menu(tab, rect, renderer);
    
    /*-------------------------------------------------------*/
    if(renderer != NULL) SDL_DestroyRenderer(renderer);
    if(window != NULL) SDL_DestroyWindow(window);
    free(tab);
    free(rect);
    SDL_Quit();
    return EXIT_SUCCESS;
}
