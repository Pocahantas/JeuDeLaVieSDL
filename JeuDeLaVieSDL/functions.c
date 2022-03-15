#include "functions.h"

void showTab(char *tab){
    int i, j;
    printf("--------------------------\n");
    for(j=0;j<LIGNES;j++){
        for(i=0;i<COLONNES;i++){
            printf("%c", tab[j * COLONNES + i]);
        }
        printf("\n");
    }
    int x = 1, y = 1;
    if(tab[y * COLONNES + (x + 1 + COLONNES)%COLONNES] == CELLALIVE) printf("droite\n"); //voisin de droite
    if(tab[y * COLONNES + (x - 1 + COLONNES)%COLONNES] == CELLALIVE) printf("gauche\n"); //voisin de gauche
    if(tab[((y + 1 + LIGNES)%LIGNES) * COLONNES + x] == CELLALIVE) printf("bas\n"); //voisin du bas
    if(tab[((y - 1 + LIGNES)%LIGNES) * COLONNES + x] == CELLALIVE) printf("haut\n"); //voisin du haut
    if(tab[((y + 1 + LIGNES)%LIGNES) * COLONNES + (x + 1 + COLONNES)%COLONNES] == CELLALIVE) printf("bas droite\n"); //voisin bas droite
    if(tab[((y - 1 + LIGNES)%LIGNES) * COLONNES + (x + 1 + COLONNES)%COLONNES] == CELLALIVE) printf("haut droite\n"); //voisin haut droite
    if(tab[((y + 1 + LIGNES)%LIGNES) * COLONNES + (x - 1 + COLONNES)%COLONNES] == CELLALIVE) printf("bas gauche\n"); //voisin bas gauche
    if(tab[((y - 1 + LIGNES)%LIGNES) * COLONNES + (x - 1 + COLONNES)%COLONNES] == CELLALIVE) printf("haut gauche\n"); //voisin haut gauche
    printf("--------------------------\n");
}

void showGen(char *tab, SDL_Rect *rect, SDL_Renderer *renderer){
    int i, j;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(j=0;j<LIGNES;j++){
        for(i=0;i<COLONNES;i++){
            if(tab[j * COLONNES + i] == CELLALIVE){
                SDL_RenderDrawRect(renderer, &rect[j * COLONNES + i]);
                SDL_RenderFillRect(renderer, &rect[j * COLONNES + i]);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

int nombreVoisins(char *tab, int x, int y){
    int cpt=0;
    if(tab[y * COLONNES + (x + 1 + COLONNES)%COLONNES] == CELLALIVE) cpt++; //voisin de droite
    if(tab[y * COLONNES + (x - 1 + COLONNES)%COLONNES] == CELLALIVE) cpt++; //voisin de gauche
    if(tab[((y + 1 + LIGNES)%LIGNES) * COLONNES + x] == CELLALIVE) cpt++; //voisin du bas
    if(tab[((y - 1 + LIGNES)%LIGNES) * COLONNES + x] == CELLALIVE) cpt++; //voisin du haut
    if(tab[((y + 1 + LIGNES)%LIGNES) * COLONNES + (x + 1 + COLONNES)%COLONNES] == CELLALIVE) cpt++; //voisin bas droite
    if(tab[((y - 1 + LIGNES)%LIGNES) * COLONNES + (x + 1 + COLONNES)%COLONNES] == CELLALIVE) cpt++; //voisin haut droite
    if(tab[((y + 1 + LIGNES)%LIGNES) * COLONNES + (x - 1 + COLONNES)%COLONNES] == CELLALIVE) cpt++; //voisin bas gauche
    if(tab[((y - 1 + LIGNES)%LIGNES) * COLONNES + (x - 1 + COLONNES)%COLONNES] == CELLALIVE) cpt++; //voisin haut gauche
    return cpt;
}

void tabGenPlusOne(char *tab, SDL_Rect *rect, SDL_Renderer *renderer){
    char *tabtemp;
    int i, j, n;
    tabtemp = (char*)malloc(sizeof(char)*COLONNES*LIGNES);
    for(j=0;j<LIGNES;j++){
        for(i=0;i<COLONNES;i++){
            n = nombreVoisins(tab, i, j);
            if(n==3) tabtemp[j*COLONNES + i] = CELLALIVE;
            else if(n==2) tabtemp[j*COLONNES + i] = tab[j*COLONNES + i];
            //else {
                //if(RECENTDEADYESNO == 1 && tab[j*COLONNES + i] == CELLALIVE) tabtemp[j*COLONNES + i] = RECENTDEAD;
                else tabtemp[j*COLONNES + i] = CELLDEAD;
            //}
        }
    }
    for(j=0;j<LIGNES;j++){
        for(i=0;i<COLONNES;i++){
            tab[j*COLONNES + i] = tabtemp[j*COLONNES + i];
        }
    }
    if(MUTATIONYESNO==1){
        for(j=0;j<LIGNES;j++){
            for(i=0;i<COLONNES;i++){
                if(rand()%1000+1 <= TAUXMUT) tab[j * COLONNES + i] = CELLALIVE;
                if(rand()%1000+1 <= TAUXAPO) tab[j * COLONNES + i] = CELLDEAD;
            }
        }
    }
    free(tabtemp);
    showGen(tab, rect, renderer);
}

void randomInput(char *tab, SDL_Rect *rect, SDL_Renderer *renderer){
    int i, j;
    for(j=0;j<LIGNES;j++){
        for(i=0;i<COLONNES;i++){
            if(rand()%2+1 == 1) tab[j * COLONNES + i] = CELLDEAD;
            else tab[j * COLONNES + i] = CELLALIVE;
        }
    }
    showGen(tab, rect, renderer);
}

void iniTab(char *tab, SDL_Rect *rect){
    int i, j;
    for(j=0;j<LIGNES;j++){
        for(i=0;i<COLONNES;i++){
            tab[j * COLONNES + i] = CELLDEAD;
            rect[j * COLONNES + i].x = i*(SQUARESIZE+1);
            rect[j * COLONNES + i].y = j*(SQUARESIZE+1);
            rect[j * COLONNES + i].w = SQUARESIZE;
            rect[j * COLONNES + i].h = SQUARESIZE;
        }
    }
}

void gameLoop(char *tab, SDL_Rect *rect, SDL_Renderer *renderer, int gameMode){
    SDL_bool programLaunched = SDL_TRUE;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    if(gameMode == 1) randomInput(tab, rect, renderer);
    while(programLaunched){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            programLaunched = SDL_FALSE;
                            break;
                        case SDLK_SPACE:
                            tabGenPlusOne(tab, rect, renderer);
                            continue;
                        default:
                            continue;
                    }
                case SDL_QUIT:
                    programLaunched = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
    }
}

void menu(char *tab, SDL_Rect *rect, SDL_Renderer *renderer){
    SDL_bool programLaunched = SDL_TRUE;
    //Où mettre le sprite de menu
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    while(programLaunched){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            programLaunched = SDL_FALSE;
                            break;
                        case SDLK_a:
                            gameLoop(tab, rect, renderer, 1);
                            break;
                        case SDLK_z:
                            gameLoop(tab, rect, renderer, 2);
                        default:
                            continue;
                    }
                case SDL_QUIT:
                    programLaunched = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
    }
}
