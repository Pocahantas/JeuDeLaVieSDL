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
    
    
    /*
    SDL_Rect rect = {100, 100, 10, 10};
    SDL_Rect menu = {200, 200, 400, 400};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &menu);
    SDL_RenderFillRect(renderer, &menu);
    SDL_RenderPresent(renderer);

    while(program_launched){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_d:
                            rect.x += 10;
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                            SDL_RenderClear(renderer);
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                            SDL_RenderDrawRect(renderer, &rect);
                            SDL_RenderFillRect(renderer, &rect);
                            SDL_RenderPresent(renderer);
                            continue;
                        default:
                            continue;
                    }
                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
    }
    */

    /*-------------------------------------------------------*/
    if(renderer != NULL) SDL_DestroyRenderer(renderer);
    if(window != NULL) SDL_DestroyWindow(window);
    free(tab);
    free(rect);
    SDL_Quit();
    return EXIT_SUCCESS;
}
