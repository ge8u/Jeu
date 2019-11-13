#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "fonctions_fichers.h"
#include "fonctions_SDL.h"
#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_image.h>

int main(){
    //ex1
    int nbLig=0;
    int nbCol=0;
    char** G=allouer_tab_2D(nbLig,nbCol);
    /*taille_fichier("tabChiffres.txt",&nbLig,&nbCol);
    G=allouer_tab_2D(nbLig,nbCol);
    printf("taille du fichier :%d x %d\n",nbLig,nbCol);
    printf("Le contenue du tableau(%d x %d)est:\n",nbLig,nbCol);
    G=lire_fichier("tabChiffres.txt");
    afficher_tab_2D(G,nbLig,nbCol);
    desallouer_tab_2D(G,nbLig);*/
    
    /*G=allouer_tab_2D(nbLig,nbCol);
    G=modifier_caractere(G,nbLig,nbCol,'1','a');
    ecrire_fichier("tabChiffres.txt",G,nbLig,nbCol);
    G=lire_fichier("tabChiffres.txt");
    printf("Le contenue du tableau après avoir remplacé 1 par a est :\n");
    afficher_tab_2D(G,nbLig,nbCol);
    desallouer_tab_2D(G,nbLig);*/
    
    /*taille_fichier("tabCaracteres.txt",&nbLig,&nbCol);
    G=allouer_tab_2D(nbLig,nbCol);
    printf("taille du fichier :%d x %d\n",nbLig,nbCol);
    printf("Le contenue du tableau(%d x %d)est:\n",nbLig,nbCol);
    G=lire_fichier("tabCaracteres.txt");
    afficher_tab_2D(G,nbLig,nbCol);
    desallouer_tab_2D(G,nbLig);

    taille_fichier("terrain.txt",&nbLig,&nbCol);
    G=allouer_tab_2D(nbLig,nbCol);
    printf("taille du fichier :%d x %d\n",nbLig,nbCol);
    printf("Le contenue du tableau(%d x %d)est:\n",nbLig,nbCol);
    G=lire_fichier("terrain.txt");
    afficher_tab_2D(G,nbLig,nbCol);
    desallouer_tab_2D(G,nbLig);*/
    
    //ex3
    SDL_Window* fenetre;  // Déclaration de la fenêtre
    SDL_Event evenements; // Événements liés à la fenêtre
    bool terminer = false;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
        
    }
    
    // Créer la fenêtre
    fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 1408, 641, SDL_WINDOW_RESIZABLE);
    if(fenetre == NULL) // En cas d’erreur
    {
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
        
    }
    
    // Mettre en place un contexte de rendu de l’écran
    SDL_Renderer* ecran;
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    
    // Charger l’image
    SDL_Texture* fond= charger_image( "fond.bmp", ecran );
    
    //créer le terrain
    taille_fichier("terrain.txt",&nbLig,&nbCol);
    G=allouer_tab_2D(nbLig,nbCol);
    G=lire_fichier("terrain.txt");
    afficher_tab_2D(G,nbLig,nbCol);
    
    
    // Charger l’image avec la transparence
    //Uint8 r = 255, g = 255, b = 255;
    SDL_Texture* pavage= charger_image( "pavage.bmp", ecran );
    //SDL_Texture* sprite=charger_image_transparente("sprites.bmp", ecran,0,g,b);
         
    SDL_Rect SrcR_pavage[10][16];
   // SrcR_sprite=lire_fichier("terrain.txt");
     for(int i=0; i<10; i++)
    {
        for(int j=0; j<16; j++)
        {  
            SrcR_pavage[i][j].x = j*32;
            SrcR_pavage[i][j].y = i*32;
            SrcR_pavage[i][j].w = 32; // Largeur du pavage
            SrcR_pavage[i][j].h = 32; // Hauteur du pavage
        }
    }

    
    SDL_Rect DestR_pavage[nbLig][nbCol];
   // DestR_pavage=lire_fichier("terrain.txt");
    for(int i=0; i<nbLig; i++)
    {
        for(int j=0; j<nbCol; j++)
        {
            DestR_pavage[i][j].x =j*64;
            DestR_pavage[i][j].y =i*64;
            DestR_pavage[i][j].w = SrcR_pavage[i][j].w*2; // Largeur du pavage
            DestR_pavage[i][j].h = SrcR_pavage[i][j].h*2; // Hauteur du pavage
        }
        
    }
    
     //charger le texte
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("./arial.ttf",28);
    SDL_Color color = {0,0,0,0};
    char msg[] = "TP sur Makefile et SDL";
    SDL_Texture* texte = charger_texte(msg,ecran,font,color);
    SDL_Rect text_pos; 
    
    // Position du texte
    text_pos.x = 10;
    text_pos.y = 100;
    text_pos.w = 285; // Largeur du texte en pixels (à récupérer)
    text_pos.h = 36; // Hauteur du texte en pixels (à récupérer)
    
    // Boucle principale
    while(!terminer)
    {
        SDL_RenderClear(ecran);
        SDL_RenderCopy(ecran,fond,NULL,NULL);

        for(int i=0; i<nbLig; i++)
        {
            for(int j=0;j<nbCol;j++)
            {

                    SDL_RenderCopy(ecran, pavage, &SrcR_pavage[(int)G[i][j]/16-3][(int)G[i][j]%16], &DestR_pavage[i][j]);
            }
        }
        
        while( SDL_PollEvent( &evenements ) )
            switch(evenements.type)
            {
                case SDL_QUIT:terminer = true; 
                break;
                case SDL_KEYDOWN:
                switch(evenements.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        terminer = true;  break;
                    
                }
            }
       //Appliquer la surface du texte sur l’écran
        SDL_RenderCopy(ecran,texte,NULL,&text_pos);
        SDL_RenderPresent(ecran);  
    }
    
    // Quitter SDL
    SDL_DestroyRenderer(ecran);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    
    // Fermer la police et quitter SDL_ttf
    TTF_CloseFont( font );
    TTF_Quit();
    return 0;
}
