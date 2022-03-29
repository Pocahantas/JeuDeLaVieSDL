#include "functions.h"

void showTab(char *tab){
    int i, j;
    printf("--------------------------\n");
    for(j=0;j<LIGNES;++j){
        for(i=0;i<COLONNES;++i){
            printf("%c", tab[i + j * COLONNES]);
        }
        printf("\n");
    }
    printf("--------------------------\n");
}

float ratio(char *tab){
    int i, j, cpt = 0;
    float res, size = LIGNES*COLONNES;
    for(j=0;j<LIGNES;++j){
        for(i=0;i<COLONNES;++i){
            if(tab[i + j*COLONNES] == CELLALIVE) cpt++;
        }
    }
    res = cpt/size;
    return res;
}

float ratioColor(char *tab,int *color){
    int i, j;
    float cpt = 0;
    float res;
    float size = 0;
    for(j=0;j<LIGNES;++j){
        for(i=0;i<COLONNES;++i){
            if(tab[i + j*COLONNES] == CELLALIVE) {
            	size++;
            	if(color[i+j*COLONNES]==1){
            	cpt++;
            	} 
            }
            
        }
    }
    
    res = cpt / size;
    return res;
}



void showGen(char *tab, SDL_Rect *rect, SDL_Renderer *renderer, int *colors){
    int i, j;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    if (TEAMS ==1){
    for(j=0;j<LIGNES;++j){
        for(i=0;i<COLONNES;++i){
            if(tab[i + j * COLONNES] == CELLALIVE){
            	if(colors[i+j*COLONNES] == 1){
            	
            	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            	}
            	else{
            	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            	}
                SDL_RenderDrawRect(renderer, &rect[i + j * COLONNES]);
                SDL_RenderFillRect(renderer, &rect[i + j * COLONNES]);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else if(RECENTDEADYESNO == 1 && tab[i + j * COLONNES] == RECENTDEAD){
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
                SDL_RenderDrawRect(renderer, &rect[i + j * COLONNES]);
                SDL_RenderFillRect(renderer, &rect[i + j * COLONNES]);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
        }
    }
    }
    else {
    for(j=0;j<LIGNES;++j){
        for(i=0;i<COLONNES;++i){
            if(tab[i + j * COLONNES] == CELLALIVE){
            
                SDL_RenderDrawRect(renderer, &rect[i + j * COLONNES]);
                SDL_RenderFillRect(renderer, &rect[i + j * COLONNES]);
            }
            else if(RECENTDEADYESNO == 1 && tab[i + j * COLONNES] == RECENTDEAD){
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
                SDL_RenderDrawRect(renderer, &rect[i + j * COLONNES]);
                SDL_RenderFillRect(renderer, &rect[i + j * COLONNES]);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
        }
    }
    
    }
    
    
    
    SDL_RenderPresent(renderer);
}

/*-------------------------------------------------------*/
//Pour les couleurs
void iniColors(char *tab, int *colors){
	int i, j;
	if(MODE==0){
	for(j=0; j<LIGNES;++j){
		for(i=0; i<COLONNES;++i){
			if(tab[i+j*COLONNES]==CELLALIVE){
			if(rand()%2 == 1) {
			colors[i + j * COLONNES] = 2;
			}
            		else colors[i + j * COLONNES] = 1;	
			}
		}
	}
	}
	if(MODE==1){
	for(j=0; j<LIGNES;++j){
		for(i=0; i<COLONNES;++i){
			if(tab[i+j*COLONNES]==CELLALIVE){
			if(i > COLONNES/2 && j>LIGNES/2 || (i<COLONNES/2 && j<LIGNES/2)) {
			colors[i + j * COLONNES] = 2;
			}
            		else colors[i + j * COLONNES] = 1;	
			}
		}
	}
	
	}
	if(MODE==2){
	for(j=0; j<LIGNES;++j){
		for(i=0; i<COLONNES;++i){
			if(tab[i+j*COLONNES]==CELLALIVE){
			if((i%2) ==0) {
			colors[i + j * COLONNES] = 2;
			}
            		else colors[i + j * COLONNES] = 1;	
			}
		}
	}
	}

}
/*-------------------------------------------------------*/
//Compte les couleurs autour d'une cellule naissante
int nombreColors(int *colors, int x, int y){
    int cpt=0;
    if(colors[y * COLONNES + (x + 1 + COLONNES)%COLONNES] == 1) cpt++; //voisin de droite
    if(colors[y * COLONNES + (x - 1 + COLONNES)%COLONNES] == 1) cpt++; //voisin de gauche
    if(colors[((y + 1 + LIGNES)%LIGNES) * COLONNES + x] == 1) cpt++; //voisin du bas
    if(colors[((y - 1 + LIGNES)%LIGNES) * COLONNES + x] == 1) cpt++; //voisin du haut
    if(colors[((y + 1 + LIGNES)%LIGNES) * COLONNES + (x + 1 + COLONNES)%COLONNES] == 1) cpt++; //voisin bas droite
    if(colors[((y - 1 + LIGNES)%LIGNES) * COLONNES + (x + 1 + COLONNES)%COLONNES] == 1) cpt++; //voisin haut droite
    if(colors[((y + 1 + LIGNES)%LIGNES) * COLONNES + (x - 1 + COLONNES)%COLONNES] == 1) cpt++; //voisin bas gauche
    if(colors[((y - 1 + LIGNES)%LIGNES) * COLONNES + (x - 1 + COLONNES)%COLONNES] == 1) cpt++; //voisin haut gauche
    return cpt;
}

/*-------------------------------------------------------*/

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

/*-------------------------------------------------------*/
//Fait apparaitre un glider
void glider(char *tab, int x, int y){
    int i, j;
    
    
    
	if(rand()%GLIDERDIRECTION==0 && GLIDERDIRECTION < 10001) {
    tab[y * COLONNES + (x + 1 + COLONNES)%COLONNES] = CELLALIVE ; //voisin de droite
    tab[y * COLONNES + (x - 1 + COLONNES)%COLONNES] = CELLDEAD; //voisin de gauche
    tab[((y + 1 + LIGNES)%LIGNES) * COLONNES + x] = CELLALIVE ; //voisin du bas
    tab[((y - 1 + LIGNES)%LIGNES) * COLONNES + x] = CELLALIVE; //voisin du haut
    tab[((y + 1 + LIGNES)%LIGNES) * COLONNES + (x + 1 + COLONNES)%COLONNES] = CELLALIVE; //voisin bas droite
    tab[((y - 1 + LIGNES)%LIGNES) * COLONNES + (x + 1 + COLONNES)%COLONNES] = CELLDEAD; //voisin haut droite
    tab[((y + 1 + LIGNES)%LIGNES) * COLONNES + (x - 1 + COLONNES)%COLONNES] = CELLALIVE; //voisin bas gauche
    tab[((y - 1 + LIGNES)%LIGNES) * COLONNES + (x - 1 + COLONNES)%COLONNES] = CELLDEAD; //haut gauche
    tab[y*COLONNES + x] = CELLDEAD;
    
	}
	else {
	tab[y * COLONNES + (x + 1 + COLONNES)%COLONNES] = CELLDEAD ; //voisin de droite
    tab[y * COLONNES + (x - 1 + COLONNES)%COLONNES] = CELLALIVE; //voisin de gauche
    tab[((y + 1 + LIGNES)%LIGNES) * COLONNES + x] = CELLALIVE ; //voisin du bas
    tab[((y - 1 + LIGNES)%LIGNES) * COLONNES + x] = CELLALIVE; //voisin du haut
    tab[((y + 1 + LIGNES)%LIGNES) * COLONNES + (x + 1 + COLONNES)%COLONNES] = CELLDEAD; //voisin bas droite
    tab[((y - 1 + LIGNES)%LIGNES) * COLONNES + (x + 1 + COLONNES)%COLONNES] = CELLALIVE; //voisin haut droite
    tab[((y + 1 + LIGNES)%LIGNES) * COLONNES + (x - 1 + COLONNES)%COLONNES] = CELLDEAD; //voisin bas gauche
    tab[((y - 1 + LIGNES)%LIGNES) * COLONNES + (x - 1 + COLONNES)%COLONNES] = CELLALIVE; //haut gauche
    tab[y*COLONNES + x] = CELLDEAD;
	
	
	
	}


}
/*-------------------------------------------------------*/


void tabGenPlusOne(char *tab, SDL_Rect *rect, SDL_Renderer *renderer, int gameMode, int *colors){
    char *tabtemp;
    int i, j, n, a = 0;
    tabtemp = (char*)malloc(sizeof(char)*COLONNES*LIGNES);
    int *colorstemp;
    colorstemp = calloc(COLONNES*LIGNES,sizeof(int));
    if(TEAMS==1){
    for(j=0;j<LIGNES;++j){
        for(i=0;i<COLONNES;++i){
            n = nombreVoisins(tab, i, j);
            if(n==BIRTH) {
            tabtemp[i + j * COLONNES] = CELLALIVE;
            if (rand()%3+1 <= nombreColors(colors, i ,j)){
            	colorstemp[i + j*COLONNES] = 1;
            }
            else{
            	colorstemp[i+j*COLONNES] = 2;
            }
            }
            
            else if(n==STABLE) {
            tabtemp[i + j * COLONNES] = tab[i + j * COLONNES];
            colorstemp[i+j*COLONNES] = colors[i+j*COLONNES];
            }
            
            else {
            	colorstemp[i+j*COLONNES] = 0;
                if(RECENTDEADYESNO == 1 && tab[i + j * COLONNES] == CELLALIVE) tabtemp[i + j * COLONNES] = RECENTDEAD;
                else tabtemp[i + j * COLONNES] = CELLDEAD;
            }
        }
    }
    for(j=0;j<LIGNES;++j){
        for(i=0;i<COLONNES;++i){
            tab[i + j * COLONNES] = tabtemp[i + j * COLONNES];
        }
    }
    for(j=0;j<LIGNES;++j){
        for(i=0;i<COLONNES;++i){
            colors[i + j * COLONNES] = colorstemp[i + j * COLONNES];
        }
    }
    }
    else{
    for(j=0;j<LIGNES;++j){
        for(i=0;i<COLONNES;++i){
            n = nombreVoisins(tab, i, j);
            if(n==BIRTH) {
            tabtemp[i + j * COLONNES] = CELLALIVE;
            
            }
            
            
            
            else if(n==STABLE) {
            tabtemp[i + j * COLONNES] = tab[i + j * COLONNES];
            
            }
            
            else {
            	
                if(RECENTDEADYESNO == 1 && tab[i + j * COLONNES] == CELLALIVE) tabtemp[i + j * COLONNES] = RECENTDEAD;
                else tabtemp[i + j * COLONNES] = CELLDEAD;
            }
        }
    }
    for(j=0;j<LIGNES;++j){
        for(i=0;i<COLONNES;++i){
            tab[i + j * COLONNES] = tabtemp[i + j * COLONNES];
        }
    }
    
    
    }
    if(gameMode==2){
        for(j=0;j<LIGNES;++j){
            for(i=0;i<COLONNES;++i){
                if(rand()%1000+1 <= TAUXMUT){
                    tab[i + j * COLONNES] = CELLALIVE;
                    a = 1;
                }
                if(rand()%1000+1 <= TAUXAPO){
                    if(a == 1){
                        if(rand()%2+1 == 1) tab[i + j * COLONNES] = CELLDEAD;
                        else tab[i + j * COLONNES] = CELLALIVE;
                    }
                    else tab[i + j * COLONNES] = CELLDEAD;
                }
                a = 0;
            }
        }
    }
    if(gameMode==3){
        for(j=LIGNES/3;j<LIGNES*2/3;++j){
            for(i=COLONNES/3;i<COLONNES*2/3;++i){
                if(rand()%1000+1 <= TAUXMUT){
                    tab[i + j * COLONNES] = CELLALIVE;
                    a = 1;
                }
                if(rand()%1000+1 <= TAUXAPO){
                    if(a == 1){
                        if(rand()%2+1 == 1) tab[i + j * COLONNES] = CELLDEAD;
                        else tab[i + j * COLONNES] = CELLALIVE;
                    }
                    else tab[i + j * COLONNES] = CELLDEAD;
                }
                a = 0;
            }
        }
    }
    free(tabtemp);
    free(colorstemp);
    
    showGen(tab, rect, renderer, colors);
}

void randomInput(char *tab, SDL_Rect *rect, SDL_Renderer *renderer, int *colors){
    int i, j;
    if(GLIDERS==0){
    for(j=0;j<LIGNES;++j){
        for(i=0;i<COLONNES;++i){
            if(rand()%2+1 == 1) tab[i + j * COLONNES] = CELLDEAD;
            else tab[i + j * COLONNES] = CELLALIVE;
        }
    }
    }
    if (GLIDERS==1){
    	for(j=0;j<LIGNES;++j){
        for(i=0;i<COLONNES;++i){
            tab[i + j * COLONNES] = CELLDEAD;
            
        }
    }
    if (COLLISION==0){
    for(j=3;j<LIGNES-3;++j){
        for(i=3;i<COLONNES-3;++i){
            if(rand()%GLIDERSPAWN== 1 && nombreVoisins(tab, i+2, j)==0 && nombreVoisins(tab, i+2, j+2)==0 && nombreVoisins(tab, i+2, j-2)==0 && nombreVoisins(tab, i, j+2)==0 && nombreVoisins(tab, i-2, j+2)==0 && nombreVoisins(tab, i-2, j)==0 && nombreVoisins(tab, i-2, j-2)==0 && nombreVoisins(tab, i, j-2)==0 && nombreVoisins(tab, i, j)==0) {
            glider(tab, i, j);
            
            }
            
        }
    }
    }
    if (COLLISION ==1){
    for(j=0;j<LIGNES;++j){
        for(i=0;i<COLONNES;++i){
            if(rand()%GLIDERSPAWN==1 ) {
            glider(tab, i, j);
            
            }
            
        }
    }
    
    }
    }
    showGen(tab, rect, renderer, colors);
}

void iniTab(char *tab, SDL_Rect *rect){
    int i, j;
    for(j=0;j<LIGNES;++j){
        for(i=0;i<COLONNES;++i){
            tab[i + j * COLONNES] = CELLDEAD;
            rect[i + j * COLONNES].x = i*(SQUARESIZE+1);
            rect[i + j * COLONNES].y = j*(SQUARESIZE+1);
            rect[i + j * COLONNES].w = SQUARESIZE;
            rect[i + j * COLONNES].h = SQUARESIZE;
        }
    }
}


//Etat de la cellule à une position relative (xx, yy) d'une celule point de départ (x,y)
int relCellState(char *tab, int x, int y, int xx, int yy){
    if(tab[((y + yy + LIGNES)%LIGNES) * COLONNES + (x + xx + COLONNES)%COLONNES] == CELLALIVE) return 1;
    return 0;
}

int findSquare(char *tab, int x, int y){
    if(relCellState(tab, x, y, -1, -1) == 0 && relCellState(tab, x, y, 0, -1) == 0 && relCellState(tab, x, y, 1, -1) == 0 && relCellState(tab, x, y, 2, -1) == 0 && relCellState(tab, x, y, -1, 0) == 0 && tab[x + y * COLONNES] == CELLALIVE && relCellState(tab, x, y, 1, 0) == 1 && relCellState(tab, x, y, 2, 0) == 0 && relCellState(tab, x, y, -1, 1) == 0 && relCellState(tab, x, y, 0, 1) == 1 && relCellState(tab, x, y, 1, 1) == 1 && relCellState(tab, x, y, 2, 1) == 0 && relCellState(tab, x, y, -1, 2) == 0 && relCellState(tab, x, y, 0, 2) == 0 && relCellState(tab, x, y, 1, 2) == 0 && relCellState(tab, x, y, 2, 2) == 0) return 1;
    return 0;
}

int find3LineVert(char *tab, int x, int y){
    if(relCellState(tab, x, y, -1, -1) == 0 && relCellState(tab, x, y, 0, -1) == 0 && relCellState(tab, x, y, 1, -1) == 0 && relCellState(tab, x, y, 2, -1) == 0 && relCellState(tab, x, y, 3, -1) == 0 && relCellState(tab, x, y, -1, 0) == 0 && tab[x + y * COLONNES] == CELLALIVE && relCellState(tab, x, y, 1, 0) == 1 && relCellState(tab, x, y, 2, 0) == 1 && relCellState(tab, x, y, 3, 0) == 0 && relCellState(tab, x, y, -1, 1) == 0 && relCellState(tab, x, y, 0, 1) == 0 && relCellState(tab, x, y, 1, 1) == 0 && relCellState(tab, x, y, 2, 1) == 0 && relCellState(tab, x, y, 3, 1) == 0) return 1;
    return 0;
}

int find3LineHori(char *tab, int x, int y){
    if(relCellState(tab, x, y, -1, -1) == 0 && relCellState(tab, x, y, 0, -1) == 0 && relCellState(tab, x, y, 1, -1) == 0 && relCellState(tab, x, y, -1, 0) == 0 && tab[x + y * COLONNES] == CELLALIVE && relCellState(tab, x, y, 1, 0) == 0 && relCellState(tab, x, y, -1, 1) == 0 && relCellState(tab, x, y, 0, 1) == 1 && relCellState(tab, x, y, 1, 1) == 0 && relCellState(tab, x, y, -1, 2) == 0 && relCellState(tab, x, y, 0, 2) == 1 && relCellState(tab, x, y, 1, 2) == 0 && relCellState(tab, x, y, -1, 3) == 0 && relCellState(tab, x, y, 0, 3) == 0 && relCellState(tab, x, y, -1, 3) == 0) return 1;
    return 0;
}

void cleanUp(char *tab){
    int i, j;
    for(j=0;j<LIGNES;++j){
        for(i=0;i<COLONNES;++i){
            if(rand()%4+1 <= 3){
                if(findSquare(tab, i, j) == 1){
                    tab[i + j * COLONNES] = CELLDEAD;
                    tab[(i+1) + j * COLONNES] = CELLDEAD;
                    tab[i + (j+1) * COLONNES] = CELLDEAD;
                    tab[(i+1) + (j+1) * COLONNES] = CELLDEAD;
                }
                if(find3LineVert(tab, i, j) == 1){
                    tab[i + j * COLONNES] = CELLDEAD;
                    tab[(i+1) + j * COLONNES] = CELLDEAD;
                    tab[(i+2) + j * COLONNES] = CELLDEAD;
                }
                if(find3LineHori(tab, i, j) == 1){
                    tab[i + j * COLONNES] = CELLDEAD;
                    tab[i + (j+1) * COLONNES] = CELLDEAD;
                    tab[i + (j+2) * COLONNES] = CELLDEAD;
                }
            }
        }
    }
}

int fitness(char *tab, int nbalg){
    int i, j, cpt = 0;
    for(j=0;j<LIGNES;++j){
        for(i=0;i<COLONNES;++i){
            if(tab[i + j * COLONNES] == CELLALIVE) cpt++;
            if(nbalg > 0){
                if(findSquare(tab, i, j) == 1) cpt -= 8;
                if(find3LineVert(tab, i, j) == 1) cpt -= 4;
                if(find3LineHori(tab, i, j) == 1) cpt -= 4;
            }
        }
    }
    return cpt;
}

void gameLoopGenetic(char *tab, SDL_Rect *rect, SDL_Renderer *renderer,int * colors){
    char *tabStockStart = (char*)malloc(sizeof(char)*COLONNES*LIGNES*POPTOT);
    if(NULL == tabStockStart) printf("Erreur allocation tabStockStart\n");
    char *tabStockFinish = (char*)malloc(sizeof(char)*COLONNES*LIGNES*POPTOT);
    if(NULL == tabStockFinish) printf("Erreur allocation tabStockFinish\n");
    int *tabFitness = (int*)malloc(sizeof(int)*POPTOT);
    if(NULL == tabFitness) printf("Erreur allocation tabFitness\n");
    //NE PAS OUBLIER D AJOUTER LES FREETAB A LA FIN DE LA FONCTION OU QUAND BREAK
    
    int i, j, k, l, maxk=0, indiceMaxk=0;
    SDL_bool programLaunched = SDL_TRUE;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    
    //Initialisation des 2 tableaux de stock
    for(i=0;i<COLONNES*LIGNES*POPTOT;++i){
        tabStockStart[i] = CELLDEAD;
        tabStockFinish[i] = CELLDEAD;
    }
    
    while(programLaunched){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            programLaunched = SDL_FALSE;
                            break;
                        case SDLK_e:
                            //On répète l'altgo d'évolution un nombre NBALGO de fois
                            for(l=0;l<NBALGO;++l){
                                
                                //Nombre total d'organismes étudiés à la fois = POPTOT
                                for(k=0;k<POPTOT;++k){
                                    
                                    //On prend dans tabStockStart le tab que l'on veut étudier
                                    for(j=0;j<LIGNES;++j){
                                        for(i=0;i<COLONNES;++i){
                                            tab[i + j * COLONNES] = tabStockStart[i + COLONNES * (j + LIGNES * k)];
                                        }
                                    }
                                    
                                    //Delay pour afficher précédent starttab
                                    /*
                                    if(l > 0 && k == 0){
                                        printf("Affichage tableau topfitness start\n");
                                        showGen(tab, rect, renderer);
                                        SDL_Delay(2500);
                                    }
                                     */
                                    
                                    printf("Algo numéro %d, Testing organisme %d\n", l+1, k+1);
                                    //Phase courte XGEN de mutation puis phase longue YGEN de survie/évolution sans mutation
                                    for(i=0;i<(XGEN/(l+1));++i){
                                        tabGenPlusOne(tab, rect, renderer, 3, colors);
                                    }
                                    //Plus tard accélérer le processus, stop si tab fulldead en ygen
                                    for(i=0;i<YGEN;++i){
                                        tabGenPlusOne(tab, rect, renderer, 1, colors);
                                    }
                                    
                                    //Cleanup des structures non intéressantes
                                    //if(l > 0) cleanUp(tab);
                                    
                                    //Stockage du score de fitness dans le tableau fitness
                                    tabFitness[k] = fitness(tab, l);
                                    
                                    //Stock le tableau 2D dans tabStockFinish
                                    for(j=0;j<LIGNES;++j){
                                        for(i=0;i<COLONNES;++i){
                                            tabStockFinish[i + COLONNES * (j + LIGNES * k)] = tab[i+ j * COLONNES];
                                        }
                                    }
                                }
                                
                                //On repère l'indice du tableau avec le meilleur fitness
                                //Version basique où on récupère juste le top1 meilleur fitness, et on rempli le tab start de top1
                                //Plus tard faire version où l'on rempli un certain %aléatoire du start avec un autre certain top% des meilleurs fitness
                                for(k=0;k<POPTOT;++k){
                                    if(tabFitness[k] > maxk){
                                        maxk = tabFitness[k];
                                        indiceMaxk = k;
                                    }
                                }
                                //Stockage du tableau top1fitness dans tabstart
                                for(k=0;k<POPTOT;++k){
                                    for(j=0;j<LIGNES;++j){
                                        for(i=0;i<COLONNES;++i){
                                            tabStockStart[i + COLONNES * (j + LIGNES * k)] = tabStockFinish[i + COLONNES * (j + LIGNES * indiceMaxk)];
                                        }
                                    }
                                }
                                
                                //Affichage du tableau topfitness pdt un peu de temps
                                for(j=0;j<LIGNES;++j){
                                    for(i=0;i<COLONNES;++i){
                                        tab[i + j*COLONNES] = tabStockFinish[i + COLONNES * (j + LIGNES * indiceMaxk)];
                                    }
                                }
                                printf("Affichage du tableau topfitness de l'algo numéro %d\n", l+1);
                                showGen(tab, rect, renderer, colors);
                                SDL_Delay(2000);
                                
                                maxk = 0;
                                indiceMaxk = 0;
                            }
                            for(j=0;j<LIGNES;++j){
                                for(i=0;i<COLONNES;++i){
                                    tab[i + j * COLONNES] = tabStockStart[i + j * COLONNES];
                                }
                            }
                            printf("Done\n");
                            showGen(tab, rect, renderer, colors);
                            continue;
                        case SDLK_SPACE:
                            tabGenPlusOne(tab, rect, renderer, 1, colors);
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


void gameLoop(char *tab, SDL_Rect *rect, SDL_Renderer *renderer, int gameMode, int *colors){
    int i, cpt = 0;
    SDL_bool programLaunched = SDL_TRUE;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    if(gameMode == 1) {
    randomInput(tab, rect, renderer, colors);
    iniColors(tab, colors);
    }
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
                            for(i=0;i<GENMULT;++i){
                                tabGenPlusOne(tab, rect, renderer, gameMode, colors);
                            }
                            cpt++;
                            printf("\nGen = %d,\nRatio Vivants/Morts = %f\n", cpt*GENMULT, ratio(tab));
                            if(TEAMS==1){
                            	printf("Ratio Bleu/Bleu+Rouge = %f \n", ratioColor(tab, colors));
                            
                            }
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

void menu(char *tab, SDL_Rect *rect, SDL_Renderer *renderer, SDL_Texture *texture, int *colors){
    SDL_bool programLaunched = SDL_TRUE;
    
    //Où mettre le sprite de menu
    //SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    //SDL_RenderClear(renderer);
    //SDL_RenderPresent(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
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
                            gameLoop(tab, rect, renderer, 1, colors);
                            break;
                        case SDLK_z:
                            gameLoop(tab, rect, renderer, 2, colors);
                        case SDLK_e:
                            gameLoopGenetic(tab, rect, renderer, colors);
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
