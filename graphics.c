#include "graphics.h"

void init_textures(SDL_Renderer *renderer, textures_t *textures){
  //textures->background = load_image( "./ressources/images/old/space-background.bmp",renderer);
  textures->background = load_image("./ressources/images/new/Backgrounds/background.bmp",renderer);
  textures->flare = load_image("./ressources/images/new/Menu/flare.bmp",renderer);
  textures->background_menu = load_image("./ressources/images/new/Backgrounds/purple2.bmp",renderer);
  textures->damaged_ship = load_image("./ressources/images/new/Player/newplayerDamaged.bmp",renderer);
  textures->shield_ship = load_image("./ressources/images/new/Player/newshield.bmp",renderer);
  textures->logoVaisseau = load_image("./ressources/images/new/UI/logoplayer.bmp",renderer);;
  textures->vaisseau = load_image( "./ressources/images/new/Player/player.bmp",renderer);
  textures->missile = load_image("./ressources/images/new/Player/laserPlayer.bmp",renderer);
  textures->missileEnnemi = load_image("./ressources/images/new/Player/laserEnnemi.bmp",renderer);  
  //textures->ennemi = load_image("./ressources/images/old/enemy.bmp",renderer);
  textures->ennemi = load_image("./ressources/images/new/Enemies/enemy.bmp",renderer);
  
  for (int i=0;i<NB_METEORS;i++) {
    char str2[55];
    sprintf(str2, "./ressources/images/new/Meteors/meteor%i.bmp", i);
    textures->meteor[i] = load_image(str2,renderer);
  }
  //textures->font = load_font("./ressources/images/old/arial.ttf", 14);
  textures->font = load_font("./ressources/images/new/Bonus/kenvector_future.ttf", 16);
}

void clean_textures(textures_t *textures){
  clean_texture(textures->background);
  clean_texture(textures->background_menu);
  clean_texture(textures->damaged_ship);
  clean_texture(textures->vaisseau);
  clean_texture(textures->shield_ship);
  clean_texture(textures->missile);
  clean_texture(textures->missileEnnemi);
  clean_texture(textures->logoVaisseau);
  clean_texture(textures->ennemi);

  for (int i=0;i<NB_METEORS;i++) {
    clean_texture(textures->meteor[i]);
  }

  clean_font(textures->font);
}

void apply_background(SDL_Renderer *renderer, textures_t *textures, int bgY){
  if(textures->background != NULL){
    apply_texture(textures->background, renderer, 0, bgY);
  }
}

void apply_sprite(SDL_Renderer* renderer, SDL_Texture* texture, sprite_t* sprite) {
  if (sprite->is_visible == 0)
  {
    apply_texture(texture, renderer, sprite->position_x, sprite->position_y);
  }
}

void apply_enemies(SDL_Renderer* renderer, SDL_Texture* texture, enemy_t enemies[]) {
  for (int i = 0; i<NB_ENEMIES; i++) {
    apply_sprite(renderer,texture, &enemies[i].sprite);
  }
}

void apply_meteors(SDL_Renderer* renderer, SDL_Texture* *texture, sprite_t sprites[]) {
  for (int i = 0; i<NB_METEORS; i++) {
    apply_sprite(renderer,texture[i], &sprites[i]);
  }
}

void apply_quality_text(SDL_Renderer* renderer, int x, int y, const char* text, TTF_Font* font, int size, int is_centered) {
  int width, height;
  TTF_SizeText(font, text, &width, &height);
  if(is_centered == TRUE)
    apply_text(renderer, (SCREEN_WIDTH/2-width)+x, (SCREEN_HEIGHT/2 - height)+y, width*size, height*size, text, font);
  else
    apply_text(renderer, x, y, width*size, height*size, text, font);
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){
  
  clear_renderer(renderer);
  apply_background(renderer, textures, world->bgY);
  apply_meteors(renderer, textures->meteor, world->meteors);
  apply_sprite(renderer, textures->shield_ship, &(world->shield));

  if (world->vie == 1) {
    apply_sprite(renderer, textures->damaged_ship, &(world->vaisseau));
  }
  else {
    apply_sprite(renderer, textures->vaisseau, &(world->vaisseau));
  }
  apply_sprite(renderer, textures->missile, &(world->missile));
  apply_enemies(renderer, textures->ennemi, world->enemies);

  for(int i = 0; i < NB_ENEMIES; i++)
    apply_sprite(renderer, textures->missileEnnemi, &world->enemies[i].e_missile);
  
  char str[20];
  sprintf(str, "score: %d", world->score);
  apply_quality_text(renderer, 10, 10, str, textures->font, 1, FALSE);

  char life[7];
  sprintf(life, "%d", world->vie);
  apply_quality_text(renderer, SCREEN_WIDTH-30, 10, life, textures->font, 1, FALSE);
  apply_texture(textures->logoVaisseau, renderer, SCREEN_WIDTH-SHIP_SIZE-40, 5);

  // Si le vaisseau meurt
  if (world->etat == LOSE) {
    apply_quality_text(renderer, 0, 0, "Game Over", textures->font, 2, TRUE);
  }

  // Si le joueur a detruit tout les ennemies
  if (world->etat == PERFECT) {
    apply_quality_text(renderer, 0, 0, "Perfect!", textures->font, 2, TRUE);
  }
  
  // on met à jour l'écran
  update_screen(renderer);
}

void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world){
  init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
  init_ttf();
  init_textures(*renderer,textures);
  world->gameoff = FALSE;
}
