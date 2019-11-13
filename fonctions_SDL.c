#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_image.h>

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer*renderer)
{
    SDL_Surface *S;
    S=SDL_LoadBMP(nomfichier) ;
    return SDL_CreateTextureFromSurface(renderer,S);
}

SDL_Texture* charger_image_transparente(const char* nomfichier,SDL_Renderer* renderer,Uint8 r,Uint8 g,Uint8 b)
{
    SDL_Surface *S;
    S=SDL_LoadBMP(nomfichier) ;
    Uint32 key = SDL_MapRGB(S->format,r,g,b);
    SDL_SetColorKey(S,SDL_TRUE,key);
    return SDL_CreateTextureFromSurface(renderer,S);
}

SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer,TTF_Font *font, SDL_Color color)
{
    SDL_Surface *S=TTF_RenderText_Solid(font,message,color) ;
    return SDL_CreateTextureFromSurface(renderer,S);
}
