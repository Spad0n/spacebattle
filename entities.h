#ifndef ENTITIES_H
#define ENTITIES_H

/**
 * \brief Largeur de l'écran de jeu
 */

#define SCREEN_WIDTH 300

/**
 * \brief Hauteur de l'écran de jeu
 */

#define SCREEN_HEIGHT 480

/**
 * \brief Taille d'un vaisseau
 */

#define SHIP_SIZE 32

/**
 * \brief Taille du missile en largeur
 */

#define MISSILE_WIDTH 6

/**
 * \brief Taille du missile en hauteur
 */

#define MISSILE_HEIGHT 23

/**
 * \brief La vitesse du missile
 */

#define MISSILE_SPEED 5

/**
 * \brief Le nombre d'ennemis
 */

#define NB_ENEMIES 50

/**
 * \brief La distance vertical entre deux ennemis consécutifs
 */

#define VERTICAL_DIST 2*SHIP_SIZE

/**
 * \brief La durée lorsque la partie est terminée
 */

#define END_TIME 3000

/**
 * \brief Le nombre de météors en fond
 */

#define NB_METEORS 7

/**
 * \brief taille d'un météors
 */

#define METEORS_SIZE 98

/**
 * \brief booléen vraie
 */

#define TRUE 1

/**
 * \brief booléen faux
 */

#define FALSE 0

/**
 * \brief Représentation pour stocker les sprites nécessaires à l'affichage graphique
 */

struct sprite_s{
  float position_x; /*!< Champ indiquant le coordonnés x du sprite */
  float position_y; /*!< Champ indiquant le coordonnés y du sprite */
  int largeur; /*!< Champ indiquant la largeur du sprite */
  int hauteur; /*!< Champ indiquant l'hauteur du sprite */
  int vitesse; /*!< Champ indiquant la vitesse du déplacement du sprite */
  int is_visible; /*!< Champ indiquant si le sprite est visible */
};

/**
 * \brief Type qui correspond aux sprites du jeu
 */

typedef struct sprite_s sprite_t;

/**
 * \brief Enumeration pour représenter l'état du jeu
 */

typedef enum {
  LOSE, /*!< Champ indiquant que le joueur a perdu */
  CONTINUE, /*!< Champ indiquant que le joueur n'a pas perdu et n'a pas abattu tous les ennemis */
  CLEAR, /*!< Champ indiquant que le joueur n'a pas perdu et n'a pas abattu tous les ennemis */
  PERFECT, /*!< Champ indiquant que le joueur n'a pas perdu et a abattu tous les ennemis */
} GameState;

/**
 * \brief Enumeration pour représenter les evenements d'un parry
 */

typedef enum {
  ParryDuration, /*!< Champ indiquant la durée d'un parry */
  ParryOn, /*!< Champ indiquant que le parry est activé */
  ParryOff, /*!< Champ indiquant que le parry est désactivé */
} ParryMode;

/**
 * \brief Enumeration pour représenter l'état d'un ennemi
 */

typedef enum {
  EnemyStateNormal, /*!< Champ indiquant que l'ennemi ne fait rien */
  EnemyStateShooting, /*!< Champ indiquant que l'ennemi tire */
  EnemyStateHoming, /*!< Champ indiquant que l'ennemi fonce vers le joueur */
  EnemyStateWait, /*!< Champ indiquant que l'ennemi attent */
} EnemyState;

/**
 * \brief Enumeration pour représenter le mouvement d'un ennemi
 */

typedef enum {
  UP, /*!< Champ indiquant que l'ennemi va en haut */
  DOWN, /*!< Champ indiquant que l'ennemi va en bas */
  LEFT, /*!< Champ indiquant que l'ennemi va à gauche */
  RIGHT, /*!< Champ indiquant que l'ennemi va à droite */
} EnemyMove;

/**
 * \brief Représentation des ennemis
 */

struct enemy_s {
  sprite_t sprite; /*!< Champ indiquant le sprite d'un ennemi */
  EnemyState status; /*!< Champ indiquant l'etat d'un ennemi */
  EnemyMove move; /*!< Champ indiquant le mouvement d'un ennemi */
  sprite_t e_missile; /*!< Champ indiquant le sprite d'un missile ennemi */
  int ammo; /*!< Champ indiquant le nombre de munition d'un ennemi */
};

/**
 * \brief Type qui correspond aux données d'un ennemi
 */

typedef struct enemy_s enemy_t;

#include "sdl2-audio.h"

/**
 * \brief Représentation du monde du jeu
 */

struct world_s{
  sprite_t vaisseau; /*!< Champ permettant d'afficher le vaisseau */
  int vie; /*!< Champ indiquant le nombre de vie d'un joueur */
  sprite_t missile; /*!< Champ permettant d'afficher le vaisseau */
  enemy_t enemies[NB_ENEMIES]; /*!< Champ indiquant le nombre d'ennemis */
  sprite_t meteors[NB_METEORS]; /*!< Champ indiquant le nombre de météorite */
  sprite_t shield; /*!< Champ indiquant le sprite du bouclier */
  
  int gameover; /*!< Champ indiquant si l'on est mort */
  int gameoff; /*!< Champ indiquant si l'on ferme le jeu */
  int cpt_enemies; /*!< Champ indiquant le nombre d'ennemis dépassant l'écran du bas */
  int score; /*!< Champ indiquant le nombre de points récupérer par le joueur */
  int score_wave; /*!< Champ indiquant le nombre de points récupérer dans une wave */
  int wave; /*!< Champ indiquant le nombre d'ennemis dans une wave */
  unsigned int timer; /*!< Champ indiquant la durée la fin d'une partie */
  unsigned int shield_duration; /*!< Champ indiquant la durée d'un parry */

  GameState etat; /*!< Champ indiquant l'état du jeu */
  Sounds_lib_t sounds;
  int bgY; /*!< Champ indiquant la durée d'un parry */
  ParryMode parrying; /*!< Champ indiquant l'etat d'un parry */
  SDL_TimerID id1; /*!< Champ indiquant le callback random_move */
  SDL_TimerID id2; /*!< Champ indiquant le callback change_state */
};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;


#include "graphics.h"
#include "timer.h"

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */

void init_data(world_t * world);

/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */

void clean_data(world_t *world);

/**
 * \brief La fonction genère un nombre aléatoire
 * \param a un entier
 * \param b un entier
 * \return un valeur aléatoire entre [a, b[
 */

int generate_number(int a, int b);

/**
 * \brief La fonction genère des ennemis
 * \param world les données du monde
 */

void init_enemies(world_t *world);

/**
 * \brief La fonction genère des météorite
 * \param world les données du monde
 */

void init_meteors(world_t *world);

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world);

int is_game_off(world_t *world);

/**
 * \brief La fonction vérifie si le vaisseau ne dépasse pas l'écran gauche
 * \param world les données du monde
 */

void depassement_ecran_gauche(world_t* world);

/**
 * \brief La fonction vérifie si le vaisseau ne dépasse pas l'écran droite
 * \param world les données du monde
 */

void depassement_ecran_droite(world_t* world);

/**
 * \brief La fonction vérifie si un ennemie ne dépasse pas l'écran du bas
 * \param world les données du monde
 */

void depassement_ecran_bas(world_t* world);

/**
 * \brief La fonction vérifie si un ennemie ne dépasse pas l'écran du bas
 * \param world les données du monde
 */

void depassement_ecran_haut(world_t* world);

/**
 * \brief La fonction vérifie si le vaisseau ne dépasse pas l'écran droite
 * \param world les données du monde
*/
void compute_game(world_t *world);

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param world les données du monde
 */

void update_data(world_t *world);

/**
 * \brief La fonction met à jour les données des ennemis
 * \param world les données du monde
 */

void update_enemies(world_t* world);

/**
 * \brief La fonction qui fait bouger les météors dans le décor
 * \param world les données du monde
 */

void move_meteors(world_t* world);

/**
 * \brief La fonction qui initialise les sprites du jeu
 * \param sprite un sprite
 * \param x abscisse
 * \param y ordonné
 * \param w largeur
 * \param h hauteur
 * \param v vitesse
 */

void init_sprite(sprite_t* sprite, int x, int y, int w, int h, int v);

/**
 * \brief La fonction qui affiche les coordonnés d'un sprite
 * \param sprite un sprite
 */

void print_sprite(sprite_t* sprite);

/**
 * \brief La fonction qui rend un sprite visible
 * \param sprite un sprite
 */

void set_visible(sprite_t* sprite);

/**
 * \brief La fonction qui rend un sprite invisible
 * \param sprite un sprite
 */

void set_invisible(sprite_t* sprite);

/**
 * \brief La fonction qui vérifie une collision entre deux sprites
 * \param sprite un sprite
 * \param sprite un sprite
 * \return 1 si il y a collision, 0 sinon
 */

int sprites_collide(sprite_t* sp2, sprite_t* sp1);

/**
 * \brief La fonction qui traite une collision entre deux sprites
 * \param sprite un sprite
 * \param sprite un sprite
 */

void handle_sprites_collide(sprite_t* sp2, sprite_t* sp1);

/**
 * \brief La fonction pour mettre tout les ennemis, joueur et missiles en invisible
 * \param world les données du monde
 */

void all_invisible(world_t* world);

/**
 * \brief La fonction pour mesurer le nombre d'ennemis restant
 * \param world les données du monde
 * \return nombre d'ennemis restant
 */

int remain_enemies(world_t* world);

#endif
