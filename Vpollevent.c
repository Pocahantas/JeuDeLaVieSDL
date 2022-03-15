#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

void exitError(const char *message){
    SDL_Log("Erreur %s: %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

int main(int argc, char * argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event windowEvent;
    SDL_bool program_launched = SDL_TRUE;
    
    if(SDL_Init(SDL_INIT_VIDEO) != 0) exitError("Impossible d'initialiser SDL");
    window = SDL_CreateWindow("Jeu de la vie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if(window == NULL) exitError("SDL_CreateWindow");
    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);   Passer en fullscreen plus tard?
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) exitError("SDL_CreateRenderer");
    
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


    SDL_Rect rect= {100, 100, 10, 10};
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
    
    
    SDL_PollEvent(&windowEvent);
    SDL_Delay(5000);
    rect.x = 200;
    rect.y = 200;
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
    SDL_PollEvent(&windowEvent);
    SDL_Delay(5000);

    while(program_launched){
        if(SDL_PollEvent(&windowEvent)){
            if(SDL_QUIT == windowEvent.type) break;
        }
    }
    
    if(renderer != NULL) SDL_DestroyRenderer(renderer);
    if(window != NULL) SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
