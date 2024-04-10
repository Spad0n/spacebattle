#include "timer.h"

void time_event_start(world_t* world) {
  world->id1 = SDL_AddTimer(500, random_move, world);
  world->id2 = SDL_AddTimer(2000, change_state, world);
  //SDL_TimerID id3 = SDL_AddTimer(800, battle_mode, world);
}

unsigned int random_move(unsigned int interval, void* param) {
  //if (((world_t*)param)->etat != CONTINUE)
  //  return 0;
  //int choose_enemy = generate_number(0, NB_ENEMIES);
  int rand_position = generate_number(0, 4);

  int size = remain_enemies(((world_t*)param));
  if (size == 0)
    return 200;
  int tab[size];
  int j = 0;
  for (int i = 0; i < NB_ENEMIES; i++) {
    if (((world_t*)param)->enemies[i].sprite.is_visible != 1) {
      tab[j] = i;
      j++;
    }
  }
  int choose_enemy = tab[rand() % size];

  switch (rand_position) {
  case UP:
    ((world_t*)param)->enemies[choose_enemy].move = UP;
    break;
  case DOWN:
    ((world_t*)param)->enemies[choose_enemy].move = DOWN;
    break;
  case LEFT:
    ((world_t*)param)->enemies[choose_enemy].move = LEFT;
    break;
  case RIGHT:
    ((world_t*)param)->enemies[choose_enemy].move = RIGHT;
    break;
  }
  //printf("callback: %d\n", 200/size);
  return 200/size;
}

unsigned int shooting_state(unsigned int interval, void* param) {
  ((enemy_t*)param)->status = EnemyStateNormal;
  return 0;
}

unsigned int change_state(unsigned int interval, void* param) {
  //if (((world_t*)param)->etat != CONTINUE)
  //  return 0;

  int size = remain_enemies(((world_t*)param));
  if (size == 0)
    return 500;
  int tab[size];
  int j = 0;
  for (int i = 0; i < NB_ENEMIES; i++) {
    if (((world_t*)param)->enemies[i].sprite.is_visible != 1) {
      tab[j] = i;
      j++;
    }
  }
  int choose_enemy = tab[rand() % size];

  if (((world_t*)param)->enemies[choose_enemy].status == EnemyStateWait || ((world_t*)param)->enemies[choose_enemy].status == EnemyStateHoming)
    return 500;

  ((world_t*)param)->enemies[choose_enemy].status = generate_number(0, 2);

  switch (((world_t*)param)->enemies[choose_enemy].status) {
  case EnemyStateNormal:
    printf("enemy %d: EnemyStateNormal\n", choose_enemy);
    break;
  case EnemyStateShooting:
    printf("enemy %d: EnemyStateShooting\n", choose_enemy);
    break;
  case EnemyStateHoming:
    printf("enemy %d: EnemyStateHoming\n", choose_enemy);
    break;
  }

  return (unsigned int)generate_number(10, 1001);
}

unsigned int wave_clear(unsigned int interval, void* param) {
  ((world_t*)param)->score_wave = 0;
  ((world_t*)param)->cpt_enemies = 0;
  ((world_t*)param)->etat = CONTINUE;
  //printf("done\n");
  init_enemies(((world_t*)param));
  return 0;
}
