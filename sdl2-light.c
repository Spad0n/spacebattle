/**
 * \file sdl2-light.c
 * \brief sur-couche de SDL2 pour simplifier son utilisation pour le projet
 * \author Mathieu Constant
 * \version 0.1
 * \date 10 mars 2020
*/

#include "sdl2-light.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * \brief La fonction initialise la SDL.
 * Elle crée la fenêtre du jeu ainsi que le renderer
 *  \param window la fenêtre du jeu
 *  \param renderer le renderer
 * \param width largeur de l'écran de jeu
 * \param height hauteur de l'écran de jeu
 * \return -1 en cas d'erreur, 0 sinon
*/


int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height)
{
    if(0 != SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO))
    {
        fprintf(stderr, "Erreur initialisation de la SDL : %s", SDL_GetError());
        return -1;
    }
    if(0 != SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, window, renderer))
    {
        fprintf(stderr, "Erreur lors de la creation de l'image et du renderer : %s", SDL_GetError());
        return -1;
    }
    return 0;
}


/**
 * \brief La fonction charge une image  et renvoie la texture correspondante
 * \param path est le chemin du fichier image. Le fichier doit être obligatoirement du BMP.
 * \param renderer le renderer
 * \return la surface SDL contenant l'image. Elle renvoie NULL si le chargement a échoué
 * (ex. le fichier path n'existe pas)
*/

SDL_Texture *load_image(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = SDL_LoadBMP(path);
    if(NULL == tmp)
    {
        fprintf(stderr, "Erreur pendant chargement image BMP: %s", SDL_GetError());
        return NULL;
    }
    SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, 255, 0, 255));
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur pendant creation de la texture liee a l'image chargee: %s", SDL_GetError());
        return NULL;
    }
    return texture;
}

/**
 * \brief La fonction permet d'appliquer une texture sur le renderer à une position donnée. La hauteur et la largeur est la même que celle de la texture.
 * \param texture  la texture que l'on va appliquer
 * \param renderer le renderer qui va recevoir la texture
 * \param x l'abscisse sur le renderer de l'endroit où est appliquée texture (point en haut à gauche de la surface)
 *  \param y l'ordonnée sur le renderer de l'endroit où est appliquée texture (point en haut à gauche de la surface)
*/


void apply_texture(SDL_Texture *texture,SDL_Renderer *renderer,int x, int y){
    SDL_Rect dst = {0, 0, 0, 0};
    
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    dst.x = x; dst.y=y;
    
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    
}


/**
 * \brief La fonction nettoie une texture en mémoire
 * \param texture la texture à nettoyer
*/


void clean_texture(SDL_Texture *texture){
    if(NULL != texture){
        SDL_DestroyTexture(texture);
    }
    
}

/**
 * \brief La fonction vide le contenu graphique du renderer lié à l'écran de jeu
 * \param renderer le renderer de l'écran
*/

void clear_renderer(SDL_Renderer *renderer){
    SDL_RenderClear(renderer);
}


/**
 * \brief La fonction met à jour l'écran avec le contenu du renderer
 * \param renderer le renderer de l'écran
*/

void update_screen(SDL_Renderer *renderer){
    SDL_RenderPresent(renderer);
}

/**
 * \brief La fonction met le programme en pause pendant un laps de temps
 * \param time ce laps de temps en milliseconde
*/

void pause(int time){
    SDL_Delay(time);
}


/**
 * \brief La fonction nettoie le renderer et la fenêtre du jeu en mémoire
 * \param renderer le renderer à nettoyer
 * \param window la fenêtre à nettoyer
*/

void clean_sdl(SDL_Renderer *renderer,SDL_Window *window){
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();    
}
