#include "entities.h"
#include "graphics.h"

#define PAS2 (210/128)

/**
* \Les structures pourront être déplacées et réarrangées après c'est juste pour ne rien mélanger pour l'instant.
* \Notes : 
* \ Le menu consiste en une structure principale avec ses informations
* \ Un sous_menu est un menu plus simple, lui aussi possède un pointeur que l'on peut manipuler 
* \ Le pointer_pos_h est une valeur comprise dans [0 ; et ce qu'on veut]; par exemple pour la musique, pointer_pos_h a valeur entre [0;128]
* \ Ce qui nous permet de définir exactement le changement de volume via control_sound, voir fonction met_a_jour_son(world_t *world, menu_t *menu, int n) dans menu.c
*/

struct sous_menu_s{
	int pointer_pos_h; /*!< Position horizontale du pointeur, on peut s'en servir pour un slide*/
	int pointer_pos_v; /*!< Position verticale du pointeur */
	int vertical_choices; /*!< Nombre de choix maximums que le pointeur peut parcourir verticalement */

	int x; /*!< Position en x du sous_menu */
	int y; /*!< Position en y du sous_menu */
	int w; /*!< Width du sous_menu */
	int h; /*!< Height du sous_menu */
};

typedef struct sous_menu_s s_menu_t;

struct menu_s{
	int menu_off; /*!< Menu fermé (true ou false)*/
	int game_off; /*!< Jeu fermé (true ou false)*/
	int pointer_pos; /*!< Position du pointeur dans l'ordre des choix */
	int menu_choices; /*!< Nombre de choix maximums que le pointeur peut parcourir */

	int window_volume; /*!< Fenêtre volume fermée (true ou false)*/

	int music_volume; /*!< Paramètre du son (0 à 120) */
	int effects_volume; /*!< Paramètre du son (0 à 120) */

	float menu_vaisseau_Y;
	
	s_menu_t volume_menu; /*!< Sous_menu du volume */
	int bg_menu_X;
};

typedef struct menu_s menu_t;


/**
* \brief La fonction on off du menu
* Met le menu en off ou on
*/
void set_menu_ONOFF(menu_t *menu, int b);

/**
* \brief La fonction qui gère les événements liés au menu
* De la même manière que handle_events dans le main mais pour le menu
* \param event sdl event
* \param menu le menu
* \param world le world 
*/
void handle_events_Menu(SDL_Event *event,menu_t *menu, world_t *world);

//void update_data_Menu(menu_t *menu);

/**
* \brief La fonction is_menu_off 
* Vérifie si le menu est fermé
* \param menu le menu
* \return 1 ou 0
*/
int is_menu_off(menu_t *menu);

/**
* \brief La fonction qui initialise le menu
* \param menu le menu
*/
void init_menu(menu_t *menu);

/**
* \brief La fonction qui remet les parametres
* \param world le world 
* \param menu le menu 
* ELle remet les paramètres précédents du son pour ne pas à avoir à rechanger le volume à chaque fin de boucle de game loop (voir main pour mieux comprendre)
*/
void remets_parametres_sons(world_t *world, menu_t *menu);

/**
* \brief La fonction qui affiche le menu
* De la même manière que refreshgraphics
* \param 
*/
void Refresh_Menu(SDL_Renderer* renderer, textures_t *textures,menu_t *menu,world_t *world);
