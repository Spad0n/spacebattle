#include <time.h>
#include "entities.h"
#include "menu.h"

/**
 * \brief La fonction qui nettoye tout les éléments du jeu
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param world les données du monde
 */

void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world) {
  clean_data(world);
  clean_textures(textures);
  clean_sdl(renderer,window);
}

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world, menu_t *menu){
  const Uint8 *keystates = SDL_GetKeyboardState(NULL);
  static unsigned int firerate = 0;
  static unsigned int parry = 0;

  if (keystates[SDL_SCANCODE_LEFT]){
    world->vaisseau.position_x -= world->vaisseau.vitesse;
  }
  if (keystates[SDL_SCANCODE_RIGHT]){
    world->vaisseau.position_x += world->vaisseau.vitesse;
  }
  if (keystates[SDL_SCANCODE_SPACE] && world->etat == CONTINUE && SDL_GetTicks() > firerate && menu->menu_off) {
    world->missile.position_x = world->vaisseau.position_x + (37/2) - (6/2);        
    world->missile.position_y = world->vaisseau.position_y - 23;
    world->missile.vitesse = MISSILE_SPEED;
    play(&world->sounds.Laser_effets[0],0);
    set_visible(&world->missile);
    firerate = SDL_GetTicks()+1000;
  }

  // evenements lorsque le joueur appuie sur shield au bon moment
  if (world->parrying == ParryOff) {
    parry = 0;
  }
  if (keystates[SDL_SCANCODE_S] && world->parrying == ParryOff) {
    world->parrying = ParryOn;
  }
  if (!keystates[SDL_SCANCODE_S] && world->parrying == ParryOn) {
    world->parrying = ParryDuration;
  }
  if (world->parrying == ParryDuration) {
    parry++;
    if (10 < parry) {
      world->parrying = ParryOff;
    }
  }

  while(SDL_PollEvent(event)){
    //Si l'utilisateur a cliqué sur le X de la fenêtre
    if(event->type == SDL_QUIT){
      //On indique la fin du jeu
      world->gameoff = 1;
    }

    if(event->key.keysym.sym == SDLK_ESCAPE){
      	world->gameoff = 1;
    }
  }
}

void Menu_Loop(SDL_Event *event, menu_t *menu,textures_t *textures, SDL_Renderer* renderer,world_t *world){
  remets_parametres_sons(world,menu);

  while(!is_menu_off(menu)){//tant que le menu n'est pas fermé
    //gestion des évènements
    handle_events_Menu(event,menu,world);

    //rafraichissement de l'écran
    Refresh_Menu(renderer, textures, menu,world);

    // pause de 10 ms pour controler la vitesse de rafraichissement
    pause(30);
  }
}

void Game_Loop(world_t *world, SDL_Event *event, textures_t *textures, SDL_Renderer* renderer, menu_t *menu){
  //unsigned int ticks;
  //unsigned int lastick = 0;
  //unsigned int calc;
  while(!is_game_over(world) && !is_game_off(world)){ //tant que le jeu n'est pas fini
    //lastick = ticks;
    //ticks = SDL_GetTicks();
    //printf("%f\n",(1000.0f/(ticks - lastick)));

    //gestion des évènements
    handle_events(event,world,menu);

    //mise à jour des données liée à la physique du monde
    update_data(world);
    
    //rafraichissement de l'écran
    refresh_graphics(renderer,world,textures);
    
    // pause de 10 ms pour controler la vitesse de rafraichissement
    pause(10);
  }
}

void clean_timerid(world_t* world) {
  SDL_RemoveTimer(world->id1);
  SDL_RemoveTimer(world->id2);
}

world_t new_world(){
  world_t new;
  return new;
}

menu_t new_menu(){
  menu_t new;
  return new;
}

int main( int argc, char* args[] )
{
  SDL_Event event;
  SDL_Renderer *renderer;
  SDL_Window *window;

  //plus rapide que la mémoire vive en théorie, voir si on garde ?
  //renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  menu_t menu;
  world_t world;
  textures_t textures;

  srand(time(NULL));
  
  //initialisation du jeu
  init(&window,&renderer,&textures,&world);
  init_menu(&menu);
  init_mixer();

  while(!is_game_off(&world)){
    set_menu_ONOFF(&menu, 0);

    init_sons(&world.sounds);
    play(&world.sounds.Background_musics[1],-1);
    Menu_Loop(&event, &menu, &textures, renderer,&world);
    
    //Si le joueur a appuyé sur échap dans le menu ferme complètement le jeu
    if(is_game_off(&world)){
      break;
    }

    //Joue le son du jeu
    play(&world.sounds.Background_musics[0],-1);

    printf("Le jeu se lance \n");

    init_data(&world);
    time_event_start(&world);

    Game_Loop(&world, &event, &textures, renderer,&menu);

    printf("Le jeu se ferme \n");
    clean_timerid(&world);

    //ferme complètement le jeu
    if(is_game_off(&world)){
      break;
    }

    set_menu_ONOFF(&menu, 0);
    Menu_Loop(&event, &menu, &textures, renderer,&world);

    //ferme complètement le jeu
    if(is_game_off(&world)){
      break;
    }

    // Nouvelles variables
    world = new_world();

    //Les inits
    init_data(&world);
    init_textures(renderer,&textures);
  }

  //nettoyage final
  clean(window,renderer,&textures,&world);

  return 0;
}
