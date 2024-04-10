#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "sdl2-light.h"
#include "sdl2-ttf-light.h"
#include "entities.h"

/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
 */

struct textures_s{
  SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
  SDL_Texture* flare; /*!< Texture liée à l'image du fond de l'écran. */
  SDL_Texture* background_menu;
  SDL_Texture* vaisseau; /*!< Texture liée à l'image du vaisseau. */
  SDL_Texture* vaisseauShield;
  SDL_Texture* damaged_ship;
  SDL_Texture* shield_bonus;
  SDL_Texture* shield_ship;
  SDL_Texture* logoVaisseau;
  SDL_Texture* missile; /*!< Texture liée à l'image d'un missile. */
  SDL_Texture* missileEnnemi;
  SDL_Texture* ennemi; /*!< Texture liée à l'image d'un ennemie. */
  SDL_Texture* meteor[8]; /*!< Texture liée à l'image d'un meteors. */
  TTF_Font* font; /*!< Texture liée à la police du jeu. */
};

/**
 * \brief Type qui correspond aux textures du jeu
 */

typedef struct textures_s textures_t;


/**
 * \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param world les données du monde
 */

void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world);

/**
 * \brief La fonction qui initialise les textures du jeu
 * \param renderer le renderer
 * \param textures les textures
 */

void init_textures(SDL_Renderer *renderer, textures_t *textures);

/**
 * \brief La fonction qui nettoie les textures du jeu
 * \param textures les textures
 */

void clean_textures(textures_t *textures);

/**
 * \brief La fonction qui applique l'arrière plan du jeu
 * \param renderer le renderer
 * \param textures les textures
 */

void apply_background(SDL_Renderer *renderer, textures_t *textures, int bgY);

/**
 * \brief La fonction qui applique les sprites du jeu
 * \param sprite un sprite
 */

void apply_sprite(SDL_Renderer* renderer, SDL_Texture* texture, sprite_t* sprite);

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param textures les textures
 * \param sprites un sprite
 */

void apply_enemies(SDL_Renderer* renderer, SDL_Texture* texture, enemy_t enemies[]);

void apply_meteors(SDL_Renderer* renderer, SDL_Texture* *texture, sprite_t sprites[]);
/**
 * \brief La fonction format les textes du jeu
 * \param renderer la surface de l'écran de jeu
 * \param x coordonnés x
 * \param y coordonnés y
 * \param text le texte à afficher
 * \param font la police
 * \param size la taille de la police
 * \param is_centered booléen
 */

void apply_quality_text(SDL_Renderer* renderer, int x, int y, const char* text, TTF_Font* font, int size, int is_centered);

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */

void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures);

/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param world les données du monde
 */

void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world);

#endif
