#include "entities.h"

void init_data(world_t * world) {
  
  world->gameover = 0;
  world->gameoff = 0;
  world->cpt_enemies = 0;
  world->score = 0;
  world->score_wave = 0;
  world->wave = 3;
  world->parrying = ParryOff;
  world->etat = CONTINUE;
  world->vie = 3;
  world->bgY = -256;
  world->timer = END_TIME;
  world->shield_duration = 0;

  init_sprite(&world->vaisseau, (SCREEN_WIDTH/2)-(SHIP_SIZE/2), SCREEN_HEIGHT-SHIP_SIZE-(SHIP_SIZE/2), 37, 28, 3);
  init_sprite(&world->missile, 0, 0, MISSILE_WIDTH, MISSILE_HEIGHT, MISSILE_SPEED);
  init_sprite(&world->shield, 0, 0, 0, 0, 0);
  set_invisible(&world->shield);
  set_invisible(&world->missile);
  
  init_enemies(world);
  init_meteors(world);
}

void clean_data(world_t *world) {
}

int generate_number(int a, int b) {
  return rand()%(b-a)+a;
}

void init_enemies(world_t *world)
{
  int s = SHIP_SIZE/2;
  for (int i = 0; i<NB_ENEMIES; i++)
  {
    if (i<world->wave) {
      init_sprite(&world->enemies[i].sprite, generate_number(s/2, SCREEN_WIDTH - s*2), -(i*VERTICAL_DIST)-SHIP_SIZE, 38, 31, 2);
      world->enemies[i].move = DOWN;
      world->enemies[i].status = EnemyStateNormal;
      init_sprite(&world->enemies[i].e_missile, 0, 0, MISSILE_WIDTH, MISSILE_HEIGHT, MISSILE_SPEED);
      set_invisible(&world->enemies[i].e_missile);
      world->enemies[i].ammo = 3;

    }
    else {
      init_sprite(&world->enemies[i].sprite, 0, 0, 0, 0, 0);
      init_sprite(&world->enemies[i].e_missile, 0, 0, 0, 0, 0);
      set_invisible(&world->enemies[i].sprite);
      set_invisible(&world->enemies[i].e_missile);
      world->enemies[i].move = DOWN;
      world->enemies[i].status = EnemyStateNormal;
      world->enemies[i].ammo = 0;
    }
  }
}

void init_meteors(world_t *world)
{
  int s = METEORS_SIZE/2;
  for (int i = 0; i<NB_METEORS; i++)
  {
    init_sprite(&world->meteors[i], generate_number(0, SCREEN_WIDTH - s), -(generate_number(METEORS_SIZE,3*SCREEN_HEIGHT)), METEORS_SIZE, METEORS_SIZE, 2);
    
  }
}

int is_game_over(world_t *world) {
  return world->gameover;
}

int is_game_off(world_t *world){
  return world->gameoff;
}

void depassement_ecran_gauche(world_t* world) {
  if (world->vaisseau.position_x - SHIP_SIZE/8 < 0)
    world->vaisseau.position_x += world->vaisseau.vitesse;

  for (int i = 0; i < NB_ENEMIES; i++) {
    if (world->enemies[i].move != RIGHT && world->enemies[i].sprite.position_x - SHIP_SIZE/8 < 0)
      world->enemies[i].move = RIGHT;
  }
}

void depassement_ecran_droite(world_t* world) {
  if (world->vaisseau.position_x + SHIP_SIZE > SCREEN_WIDTH-SHIP_SIZE/8)
    world->vaisseau.position_x -= world->vaisseau.vitesse;

  for (int i = 0; i < NB_ENEMIES; i++) {
    if (world->enemies[i].move != LEFT && world->enemies[i].sprite.position_x + SHIP_SIZE > SCREEN_WIDTH-SHIP_SIZE/8)
      world->enemies[i].move = LEFT;
  }
}

void depassement_ecran_bas(world_t* world) {
  for (int i = 0; i < NB_ENEMIES; i++) {
    if (world->enemies[i].move != UP && world->enemies[i].sprite.position_y - SHIP_SIZE >= SCREEN_HEIGHT/2)
      world->enemies[i].move = UP;

    if (world->enemies[i].e_missile.position_y > SCREEN_HEIGHT + MISSILE_HEIGHT)
      set_invisible(&world->enemies[i].e_missile);

    if (world->enemies[i].sprite.position_y - SHIP_SIZE/2 >= SCREEN_HEIGHT) {
      world->cpt_enemies++;

      set_invisible(&world->enemies[i].sprite);
      printf("cpt_enemies = %d\n", world->cpt_enemies);
      world->enemies[i].sprite.position_y = 0;
    }
    //if (world->bonus.position_y > SCREEN_HEIGHT + 30) {
    //  world->bonus.position_x = generate_number(0, SCREEN_WIDTH - 15);
    //  world->bonus.position_y = -(generate_number(SCREEN_HEIGHT, 3*SCREEN_HEIGHT));
    //}

  }
  for (int i = 0; i < NB_METEORS; i++) {
    if (world->meteors[i].position_y > SCREEN_HEIGHT) {
        world->meteors[i].position_x = generate_number(0, SCREEN_WIDTH - METEORS_SIZE/2);
        world->meteors[i].position_y = -generate_number(METEORS_SIZE,3*SCREEN_HEIGHT);
      }
  }
}

void depassement_ecran_haut(world_t* world) {
  if (world->missile.position_y+MISSILE_HEIGHT < 0)
    set_invisible(&world->missile);

  for (int i = 0; i < NB_ENEMIES; i++) {
    if (world->enemies[i].move != DOWN && world->enemies[i].sprite.position_y < 0)
      world->enemies[i].move = DOWN;
  }
}


void compute_game(world_t *world) {
  
  if (world->vaisseau.is_visible == 1 && world->etat == CONTINUE) {    
    world->etat = LOSE;
    world->vie = 0;
    printf("You Lose\n");
    play(&world->sounds.Explosion_effets[0], 0);
    world->timer += SDL_GetTicks();    
  }

  if (remain_enemies(world) == 0 && world->etat == CONTINUE && world->score_wave == world->wave) {
    //world->etat = WIN;
    //world->score *= 2;
    //printf("You Win\n");
    //printf("%d points\n", world->score);
    //world->vaisseau.vitesse = 0;
    //timer_start(&world->gametime);
    
    world->score += 10;
    if (world->vie < 3) {
      play(&world->sounds.Selection_sounds[1],0);
      world->vie++;
    }
      
    world->etat = PERFECT;
    world->wave++;
    SDL_TimerID wave = SDL_AddTimer(1000, wave_clear, world);
  }

  if (remain_enemies(world) == 0 && world->etat == CONTINUE && world->cpt_enemies + world->score_wave == world->wave) {
    //world->etat = SURVIVED;
    //printf("You Survived\n");
    //world->vaisseau.vitesse = 0;
    //timer_start(&world->gametime);
    world->etat = CLEAR;
    world->wave++;
    SDL_TimerID wave = SDL_AddTimer(1000, wave_clear, world);
  }
}

void update_enemies(world_t* world) {
  for(int i = 0; i < world->wave; i++) {

    if (world->enemies[i].sprite.is_visible == 0 && world->enemies[i].status != EnemyStateWait) {
      if (world->enemies[i].status != EnemyStateHoming) {
	switch (world->enemies[i].move) {
	case UP:
	  world->enemies[i].sprite.position_y -= world->enemies[i].sprite.vitesse;
	  break;
	case DOWN:
	  world->enemies[i].sprite.position_y += world->enemies[i].sprite.vitesse;
	  break;
	case LEFT:
	  world->enemies[i].sprite.position_x -= world->enemies[i].sprite.vitesse;
	  break;
	case RIGHT:
	  world->enemies[i].sprite.position_x += world->enemies[i].sprite.vitesse;
	  break;
	}
      }
    }

    // Shooting State
    if (world->enemies[i].status == EnemyStateShooting && world->enemies[i].e_missile.is_visible == 1 && world->enemies[i].sprite.is_visible == 0) {
      if (world->enemies[i].ammo != 0) {
	world->enemies[i].e_missile.position_x = world->enemies[i].sprite.position_x + 38/2 - MISSILE_WIDTH/2;
	world->enemies[i].e_missile.position_y = world->enemies[i].sprite.position_y + 31;
	set_visible(&world->enemies[i].e_missile);
	world->enemies[i].status = EnemyStateWait;
	world->enemies[i].ammo--;
	play(&world->sounds.Laser_effets[0],0);
	printf("enemy %d ammo: %d\n", i, world->enemies[i].ammo);
	SDL_TimerID time_wait = SDL_AddTimer(900, shooting_state, &world->enemies[i]);
      } else {
	printf("enemy %d is out of ammo !\n", i);
	world->enemies[i].status = EnemyStateHoming;
      }
    }

    // Homing State
    if (world->enemies[i].status == EnemyStateHoming && world->enemies[i].sprite.is_visible == 0) {
      float diffX = world->vaisseau.position_x - world->enemies[i].sprite.position_x;
      //float diffY = world->vaisseau.position_y+80 - world->enemies[i].sprite.position_y;
      float diffY = SCREEN_HEIGHT + (SHIP_SIZE/2) - world->enemies[i].sprite.position_y;
      float distance = sqrt((diffX * diffX) + (diffY * diffY));
      float directionX = diffX / distance;
      float directionY = diffY / distance;
      world->enemies[i].sprite.position_x += directionX * world->enemies[i].sprite.vitesse*2.0;
      world->enemies[i].sprite.position_y += directionY * world->enemies[i].sprite.vitesse*2.0;
    }

    if (world->enemies[i].e_missile.is_visible == 0)
      world->enemies[i].e_missile.position_y += world->enemies[i].e_missile.vitesse;

    // Faire disparaitre les missiles des ennemis si la partie se termine
    //if (world->etat != CONTINUE)
    //  set_invisible(&world->enemies[i].e_missile);
    
    if (sprites_collide(&world->vaisseau, &world->enemies[i].e_missile)) {
      if (world->parrying == ParryDuration) {
	set_visible(&world->shield);
	play(&world->sounds.Parry,0);
	world->score += 3;
	world->parrying = ParryOff;
      } else {
	world->vie--;
      }
      set_invisible(&world->enemies[i].e_missile);
    } else if (sprites_collide(&world->vaisseau, &world->enemies[i].sprite)) {
      world->vie -= 2;
      set_invisible(&world->enemies[i].sprite);
      world->cpt_enemies++;
      //world->etat = LOSE;
    }

    if (world->vie <= 0) {
      all_invisible(world);
    }


    if (sprites_collide(&world->missile, &world->enemies[i].sprite)) {
      handle_sprites_collide(&world->missile, &world->enemies[i].sprite);
      world->score++;
      world->score_wave++;
      //sprintf(world->str, "score: %d", world->score);

    }
  }
}

void move_meteors(world_t* world) {
  for (int i = 0; i < NB_METEORS; i++) {
    
    world->meteors[i].position_y += world->meteors[i].vitesse;

  }
}

void update_data(world_t *world) {
  world->bgY+=1;
  if (world->bgY > 0)
    world->bgY = -256;

  if(world->missile.is_visible == 0)
    world->missile.position_y -= world->missile.vitesse;
  //world->bonus.position_y += world->bonus.vitesse;

  move_meteors(world);
  depassement_ecran_gauche(world);
  depassement_ecran_droite(world);
  depassement_ecran_bas(world);
  depassement_ecran_haut(world);
  world->shield.position_x = world->vaisseau.position_x-(37/4);
  world->shield.position_y = world->vaisseau.position_y-(28/2);
  update_enemies(world);
  compute_game(world);

  //if (SDL_GetTicks() > world->shield_duration)
  //  set_invisible(&world->shield);

  if (world->shield.is_visible == 0) {
    world->shield_duration++;
    //printf("test\n");
    if (world->shield_duration > 8) {
      set_invisible(&world->shield);
      world->shield_duration = 0;
    }
  }

  if(SDL_GetTicks() > world->timer && world->etat == LOSE)
    world->gameover = 1;
}

void init_sprite(sprite_t* sprite, int x, int y, int w, int h, int v) {
  sprite->position_x = x;
  sprite->position_y = y;
  sprite->largeur = w;
  sprite->hauteur = h;
  sprite->vitesse = v;
  sprite->is_visible = 0;
}

void print_sprite(sprite_t* sprite) {
  printf("position_x: %f\n"
	 "position_y: %f\n"
	 "largeur: %d\n"
	 "hauteur: %d\n"
	 "vitesse: %d\n",
	 sprite->position_x,
	 sprite->position_y,
	 sprite->largeur,
	 sprite->hauteur,
	 sprite->vitesse);
}

void set_visible(sprite_t* sprite)
{
  sprite->is_visible = 0;
}

void set_invisible(sprite_t* sprite)
{
  sprite->is_visible = 1;
}

int sprites_collide(sprite_t* sp2, sprite_t* sp1) {
  int distanceX = abs(sp1->position_x + sp1->largeur/2 - (sp2->position_x + sp2->largeur/2));
  int distanceY = abs(sp1->position_y + sp1->hauteur/2 - (sp2->position_y + sp2->hauteur/2));
  
  if (sqrt(distanceX*distanceX + distanceY*distanceY) <= (sp2->largeur/2 + sp1->largeur/2) && sp1->is_visible == 0 && sp2->is_visible == 0)
    return 1;
  return 0;

  //if (abs(sp1->position_x - sp2->position_x) <= (32/2 + 32/2) && (abs(sp1->position_y - sp2->position_y) <= 32/2 + 32/2))
  //  return 1;
  //return 0;
}

void handle_sprites_collide(sprite_t* sp1, sprite_t* sp2) {
  if (sp1->is_visible == 0 && sp2->is_visible == 0) {
    sp1->vitesse = 0;
    sp2->vitesse = 0;
    sp1->is_visible = 1;
    sp2->is_visible = 1;
  }
}

void all_invisible(world_t* world) {
  world->vaisseau.vitesse = 0;
  set_invisible(&world->vaisseau);
  world->missile.vitesse = 0;
  set_invisible(&world->missile);
  for (int i = 0; i < NB_ENEMIES; i++) {
    world->enemies[i].sprite.vitesse = 0;
    world->enemies[i].e_missile.vitesse = 0;
    set_invisible(&world->enemies[i].sprite);
    set_invisible(&world->enemies[i].e_missile);
  }
}

int remain_enemies(world_t* world) {
  int j = 0;
  for (int i = 0; i < NB_ENEMIES; i++) {
    if (world->enemies[i].sprite.is_visible != 1)
      j++;
  }
  return j;
}
