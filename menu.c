#include "menu.h"

void set_menu_ONOFF(menu_t *menu, int b){
    if(b){
        menu->menu_off = 1;
    }
    else{
        menu->menu_off = 0;
    }
}

/**
* \brief La fonction qui et à jour le son
* \param world le world 
* \param menu le menu 
* \param n l'entier qui désigne le choix, 0 étant music_volume et 1 effects volume
* La fonction sert à mettre à jour le son du jeu via control_sound
* Par exemple si j'augmente le son de la musique (music_volume), j'assigne la valeur de pointer_pos_h à l'instant t (qui vient d'être modifié d'où le call de la fonction)
*/
void met_a_jour_son(world_t *world, menu_t *menu, int n){
    if(n==0){
        menu->music_volume = menu->volume_menu.pointer_pos_h;
        //Le paramètre de background_musics[1] permet juste de savoir que c'est une musique, ça aurait pu être le musics[0]
        control_sound(&world->sounds.Background_musics[1], menu->music_volume);
    }

    else{
        menu->effects_volume = menu->volume_menu.pointer_pos_h;
        control_sound(&world->sounds.Explosion_effets[0], menu->effects_volume);
        control_sound(&world->sounds.Selection_sounds[0], menu->effects_volume);
        control_sound(&world->sounds.Selection_sounds[1], menu->effects_volume);
        control_sound(&world->sounds.Laser_effets[0], menu->effects_volume);
        control_sound(&world->sounds.Parry, menu->effects_volume);
    }
}

void remets_parametres_sons(world_t *world, menu_t *menu){
    control_sound(&world->sounds.Background_musics[1], menu->music_volume);
    control_sound(&world->sounds.Explosion_effets[0], menu->effects_volume);
    control_sound(&world->sounds.Selection_sounds[0], menu->effects_volume);
    control_sound(&world->sounds.Selection_sounds[1], menu->effects_volume);
    control_sound(&world->sounds.Laser_effets[0], menu->effects_volume);
    control_sound(&world->sounds.Parry, menu->effects_volume);
}

/**
* \brief La fonction qui et à jour le son
* \param world le world 
* \param menu le menu 
* \param n n l'entier qui désigne le choix, 0 étant music_volume et 1 effects volume
* \param s le signe, permet de soustraire ou d'ajouter ex :     (si s = -1   alors   10 + (s)5 = 5)   mais si s = 1   alors   10 + (s)5 = 15
*   En réalité la fonction update_bar ne permet pas à proprement parler de mettre à jour la barre de slide du son sélectionné. 
*   ELle sert plutôt à mettre à jour le pointeur horizontal (pointer_pos_h) et de retenir sa taille dans son volume (voir met_a_jour_son en détail)
*   Sinon, la fonction est assez simple, elle vérifie que les différents sons récupèrent bien des valeurs entre 0 et 128
*   Dans la fonction on peut se demande ce qu'est slide_resistence. Il s'agit tout simplement de l'incrément. En gros à quelle vitesse on va atteindre 128 ou descendre à 0.
*   Il suffit d'y mettre un multiple de 2. Car 2^7 = 128.
*/
void update_bar(world_t *world, menu_t *menu, int n, int s){
    play(&world->sounds.Selection_sounds[0],0);
    int slide_resistence = 4;

    if (n==0){
        menu->volume_menu.pointer_pos_h = menu->music_volume;
        if(s == -1){
            if(menu->music_volume > 0){
                menu->volume_menu.pointer_pos_h -= slide_resistence;
                met_a_jour_son(world, menu, 0);
            }
        }else{
            if(128 > menu->music_volume){
                menu->volume_menu.pointer_pos_h += slide_resistence;
                met_a_jour_son(world, menu, 0);
            }
        }
    }
    else{
        menu->volume_menu.pointer_pos_h = menu->effects_volume;
        if(s == -1){
            if(menu->effects_volume > 0){
                menu->volume_menu.pointer_pos_h -= slide_resistence;
                met_a_jour_son(world, menu, 1);
            }
        }else{
            if(128 > menu->effects_volume){
                menu->volume_menu.pointer_pos_h += slide_resistence;
                met_a_jour_son(world, menu, 1);
            }
        }
    }
}

void handle_events_Menu(SDL_Event *event,menu_t *menu, world_t *world){
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

    while(SDL_PollEvent(event)){
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameoff = TRUE;
            set_menu_ONOFF(menu, TRUE);
        }
        //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
            //Si les autres fenêtres sont fermées
            if(!menu->window_volume){ 
                //Pointeur vers le haut
                if (event->key.keysym.sym == SDLK_UP){
                    play(&world->sounds.Selection_sounds[0],0);
                    menu->pointer_pos -= 1;
                    if (menu->pointer_pos < 0){
                        menu->pointer_pos = 2;
                    }
                }

                //Pointeur vers le bas
                if (event->key.keysym.sym == SDLK_DOWN){
                    play(&world->sounds.Selection_sounds[0],0);
                    menu->pointer_pos += 1;
                    if (menu->pointer_pos > menu->menu_choices){
                        menu->pointer_pos = 0;
                    }
                }

                if(event->key.keysym.sym == SDLK_SPACE){ 
                    if(menu->pointer_pos == 0){
                        menu->window_volume = TRUE;
                    }

                    if(menu->pointer_pos == 1){
                        menu->menu_off = TRUE;
                    }

                    if(menu->pointer_pos == 2){
                        world->gameoff = TRUE;
                        menu->menu_off = TRUE;
                    }
                }
            }

            //Si la fenêtre du volume est ouverte
            else if(menu->window_volume){
                if(event->key.keysym.sym == SDLK_LEFT){
                    //Si sur menu volume
                    if(menu->volume_menu.pointer_pos_v == 0){
                        update_bar(world, menu,0,-1);
                    }
                    //Si sur effects volume
                    else if(menu->volume_menu.pointer_pos_v == 1){
                        update_bar(world,menu,1,-1);
                    }
                }

                if(event->key.keysym.sym == SDLK_RIGHT){
                    //Si sur menu volume
                    if(menu->volume_menu.pointer_pos_v == 0){
                        update_bar(world, menu,0,1);
                    }
                    //Si sur effects volume
                    else if(menu->volume_menu.pointer_pos_v == 1){
                        update_bar(world,menu,1,1);
                    }
                }

                //Descend
                if(event->key.keysym.sym == SDLK_DOWN){
                    play(&world->sounds.Selection_sounds[0],0);
                    menu->volume_menu.pointer_pos_v += 1;
                    if(menu->volume_menu.pointer_pos_v > menu->volume_menu.vertical_choices){
                        menu->volume_menu.pointer_pos_v = 0;
                    }
                }

                //Remonte
                if(event->key.keysym.sym == SDLK_UP){
                    play(&world->sounds.Selection_sounds[0],0);
                    menu->volume_menu.pointer_pos_v -= 1;

                    if(menu->volume_menu.pointer_pos_v < 0){
                        menu->volume_menu.pointer_pos_v = menu->volume_menu.vertical_choices;
                    }
                }

                //Ferme le sous-menu volume
                if(event->key.keysym.sym == SDLK_SPACE){
                    play(&world->sounds.Selection_sounds[0],0);
                    if(menu->volume_menu.pointer_pos_v == menu->volume_menu.vertical_choices){
                        menu->window_volume = 0;
                    }
                }
            }

            //Si la fenêtre de score est ouverte
            else if(is_game_over(world)){
                if(event->key.keysym.sym == SDLK_SPACE){
                    set_menu_ONOFF(menu, TRUE);
                }
            }

            // Dans le menu de base
            if(event->key.keysym.sym == SDLK_ESCAPE){
                world->gameoff = 1;
                set_menu_ONOFF(menu, 1);
            }
        }
    }
}

int is_menu_off(menu_t *menu){
    return menu->menu_off;
}

void init_menu(menu_t *menu){
    //Paramètres de base du menu
    menu->menu_off = FALSE;
    menu->game_off = FALSE;
    menu->pointer_pos = 1;
    menu->menu_choices = 2;
    menu->window_volume = FALSE;
    menu->music_volume = 64;
    menu->effects_volume = 64;
    menu->bg_menu_X = -512;
    menu->menu_vaisseau_Y = 260;
    //Initiaisation du sous-menu volume dans le menu
    s_menu_t volume_menu;
    
    volume_menu.pointer_pos_h = 64;
    volume_menu.pointer_pos_v = 0;
    volume_menu.vertical_choices = 2;
    volume_menu.x = 35; 
    volume_menu.y = 80; 
    volume_menu.w = 220; 
    volume_menu.h = 350;

    menu->volume_menu = volume_menu;
}

void score_menu(menu_t *menu,SDL_Renderer* renderer, textures_t *textures,world_t *world){
    //background
    apply_texture(textures->background_menu, renderer, menu->bg_menu_X, 0);

    //Affiche les boutons
    char str[20];
    sprintf(str, "Score: %d", world->score);

    //apply_text(renderer, 10, 10, 100, 40, str, textures->font);
    //apply_quality_text(renderer, SCREEN_WIDTH/2 - 40, 100, "You died!", textures->font, 1);

    apply_quality_text(renderer, 0, -70, "You died!", textures->font, 2, TRUE);

    apply_quality_text(renderer, 40, 0, str, textures->font,1, TRUE);

    apply_quality_text(renderer, 70, 200, "Press SPACE", textures->font,1, TRUE);

    //Modifie la position du background
    menu->bg_menu_X+=1;
    if (menu->bg_menu_X > 0){
        menu->bg_menu_X = -512;
    }
}

/**
* \brief La fonction qui et à jour le son
* \param menu le menu 
* \param renderer le renderer
* \param textures les textures
*   Affiche la fenêtre du volume
*/
void volume_menu(menu_t *menu,s_menu_t *s_menu, SDL_Renderer* renderer, textures_t *textures){
    int ratio = 1.5;

    //Fenêtre sous-menu volume
    int x = s_menu->x;
    int y = s_menu->y;
    int w = s_menu->w;
    int h = s_menu->h;
    
    //Fenêtre sous-menu volume
    SDL_Rect rect = {x, y, w+5, h+5};
    SDL_SetRenderDrawColor(renderer, 105, 105, 105, 0);
    SDL_RenderFillRect(renderer, &rect);

    SDL_Rect rect2 = {x+5, y+5, w-5, h-5};
    SDL_SetRenderDrawColor(renderer, 94,63,107, 0);
    SDL_RenderFillRect(renderer, &rect2);

    //Barre menu sound
    apply_quality_text(renderer, (x/2) + 40, 100, "Music", textures->font,1, FALSE);

    SDL_Rect rect3 = {(x) + 15, 130, menu->music_volume*1.5, 10};
    if(s_menu->pointer_pos_v == 0){
        SDL_SetRenderDrawColor(renderer, 255,250,250, 0);
    }
    else{
        SDL_SetRenderDrawColor(renderer, 105, 105, 105, 0);
    }
    SDL_RenderFillRect(renderer, &rect3);

    //Barre effects sound
    apply_quality_text(renderer, (x/2) + 40, 160, "Effects sounds", textures->font,1, FALSE);

    SDL_Rect rect4 = {(x) + 15, 190, menu->effects_volume*1.5, 10};
    if(s_menu->pointer_pos_v == 1){
        SDL_SetRenderDrawColor(renderer, 255,250,250, 0);
    }
    else{
        SDL_SetRenderDrawColor(renderer, 105, 105, 105, 0);
    }

    SDL_RenderFillRect(renderer, &rect4);

    //Bouton return
    apply_quality_text(renderer, (x/2) + 95, 390, "Return", textures->font, 1,FALSE);

    if(s_menu->pointer_pos_v == s_menu->vertical_choices){
        apply_quality_text(renderer, (x/2) + 180, 390, "<-", textures->font, 1,FALSE);
    }

}

void Refresh_Menu(SDL_Renderer* renderer, textures_t *textures,menu_t *menu, world_t *world){
    clear_renderer(renderer);

    if(!is_game_over(world)){
        //Bouton, background, vaisseau
        apply_texture(textures->background_menu, renderer, menu->bg_menu_X, 0);
        apply_texture(textures->flare, renderer, -90, -80);

        apply_texture(textures->vaisseau, renderer, 50, menu->menu_vaisseau_Y);

        apply_text(renderer, 20, 10, 250, 70, "Space Battle", textures->font);


        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        //Affiche les boutons
        apply_quality_text(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, "Volume", textures->font,1, FALSE);
        apply_quality_text(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 100, "Play", textures->font,1, FALSE);
        apply_quality_text(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 200, "Quit", textures->font,1, FALSE);

        //Affiche le pointeur de choix
        if(!menu->window_volume){
            apply_quality_text(renderer, SCREEN_WIDTH/2 + 100 , SCREEN_HEIGHT/2 + (menu->pointer_pos * 100), "<-", textures->font, 1,FALSE);
        }

        //Affiche le sous-menu son si ouvert
        if(menu->window_volume){
            volume_menu(menu,&(menu->volume_menu), renderer, textures);
        }

        //Modifie la position du background
        menu->bg_menu_X+=1;
        if (menu->bg_menu_X > 0){
            menu->bg_menu_X = -512;
        }

        static float a;
        if (menu->menu_vaisseau_Y >= 260)
          a=-0.5;
        if (menu->menu_vaisseau_Y < 240) {
          a=0.5;
        }
        menu->menu_vaisseau_Y += a;
    }
    //Modifie la position du background
    
    else {
        score_menu(menu,renderer,textures,world);
    }

    //Remets la couleur de fond en noir
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // on met à jour l'écran
    update_screen(renderer);
}


