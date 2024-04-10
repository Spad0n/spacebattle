#include "entities.h"

/**
 * \brief La fonction qui test les coordonnés initialisé aux sprites du jeu
 * \param sprite un sprite
 * \param x abscisse
 * \param y ordonné
 * \param w largeur
 * \param h hauteur
 * \param v vitesse
 */

void test_init_sprite_param(sprite_t* sprite, int x, int y, int w, int h, int v) {
  init_sprite(sprite, x, y, w, h, v);
  print_sprite(sprite);
}

void print_depassement_ecran_gauche(world_t* world) {
  if (world->vaisseau.position_x - SHIP_SIZE/8 < 0)
    printf("le vaisseau dépasse l'écran\n");
  else
    printf("le vaisseau ne dépasse pas l'écran\n");
}

void print_depassement_ecran_droite(world_t* world) {
  if (world->vaisseau.position_x + SHIP_SIZE > SCREEN_WIDTH-SHIP_SIZE/8)
    printf("le vaisseau dépasse l'écran\n");
  else
    printf("le vaisseau ne dépasse pas l'écran\n");
}

void print_depassement_ecran_bas(world_t* world) {
  if (world->ennemi.position_y - SHIP_SIZE/2 >= SCREEN_HEIGHT)
    printf("l'ennemi depasse l'écran\n");
  else
    printf("l'ennemi ne dépasse pas l'écran\n");
}

/**
 * \brief La fonction test qui initialise les sprites du jeu
 */

void test_init_sprite() {
  // Déclaration de la structure du monde à tester
  world_t world;

  printf("Coordonnés du vaisseau\n");
  test_init_sprite_param(&world.vaisseau, (SCREEN_WIDTH/2)-(SHIP_SIZE/2), SCREEN_HEIGHT-SHIP_SIZE-(SHIP_SIZE/2), SHIP_SIZE, SHIP_SIZE, 5);
  print_depassement_ecran_gauche(&world);
  print_depassement_ecran_droite(&world);

  printf("\nCoordonnés de ennemi\n");
  test_init_sprite_param(&world.ennemi, (SCREEN_WIDTH/2)-(SHIP_SIZE/2), 0, SHIP_SIZE, SHIP_SIZE, 2);
  print_depassement_ecran_bas(&world);

  printf("\nCoordonnés d'un missile\n");
  test_init_sprite_param(&world.missile, 0, 0, MISSILE_SIZE, MISSILE_SIZE, MISSILE_SPEED);

  printf("\n");


  // Fonction sprites_collide
  while (sprites_collide(&world.vaisseau, &world.ennemi) == 0 && world.ennemi.position_y < SCREEN_HEIGHT) {
    world.ennemi.position_y += 1;
    if (sprites_collide(&world.vaisseau, &world.ennemi) == 1) {
      printf("collision entre le vaisseau et l'ennemi\n\n");

      // Fonction handle_sprites_collide
      handle_sprites_collide(&world.vaisseau, &world.ennemi);
      if (world.vaisseau.is_visible)
	printf("le vaisseau est invisible\n");
      if (world.ennemi.is_visible)
	printf("l'ennemi est invisible\n");
    }
  }

  // Fonction init_enemies
  init_enemies(&world);
  printf("position initiale des ennemies\n");
  for(int i = 0; i < NB_ENEMIES; i++)
    printf("position x de l'ennemi %d : %d\n"
	   "position y de l'ennemi %d : %d\n\n", i, world.enemies[i].position_x, i, world.enemies[i].position_y);

  printf("position apres la fonction `update_enemies`\n");

  // Affiche les deplacements des ennemies
  update_ennemies(&world);
  for(int i = 0; i < NB_ENEMIES; i++)
    printf("position x de l'ennemi %d : %d\n"
	   "position y de l'ennemi %d : %d\n\n", i, world.enemies[i].position_x, i, world.enemies[i].position_y);
}

int main( int argc, char* args[] )
{
  int x;
  srand(time(NULL));

  printf("création des valeurs aléatoire :\n");
  printf("[ ");
  for (int i = 0; i < 10; i++) {
    x = generate_number(2, 9);
    printf("%d ", x);
  }
  printf("]\n");
  printf("SPACEBATTLE MODE: TESTS\n\n");
  test_init_sprite();
  return 0;
}
