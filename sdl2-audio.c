#include "sdl2-audio.h"

void init_mixer(){
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44200,MIX_DEFAULT_FORMAT,2,2048);
}

void init_sons(Sounds_lib_t * lib){
    sounds_t explosion = {
        "explosion",
        CHUNK,
        Mix_LoadWAV("./ressources/sound/explosion1.ogg"),
        NULL
    };

    sounds_t laser = {
        "laser1",
        CHUNK,
        Mix_LoadWAV("./ressources/sound/Laser1.wav"),
        NULL
    };

    sounds_t select = {
        "menuselect",
        CHUNK,
        Mix_LoadWAV("./ressources/sound/menuselect.ogg"),
        NULL
    };

    sounds_t winhealth = {
        "winhealth",
        CHUNK,
        Mix_LoadWAV("./ressources/sound/winhealth.mp3"),
        NULL
    };

    sounds_t parry = {
      "parry",
      CHUNK,
      Mix_LoadWAV("./ressources/sound/parry.mp3"),
      NULL
    };

    sounds_t backgroundMusic1 = {
        "OrbitalColossus",
        MUSIC,
        NULL,
        Mix_LoadMUS("./ressources/sound/OrbitalColossus.mp3")
    };

    sounds_t backgroundMusicMenu = {
        "backgroundMusicMenu",
        MUSIC,
        NULL,
        Mix_LoadMUS("./ressources/sound/menu.wav")
    };
    
    lib->Background_musics[0] = backgroundMusic1;
    lib->Background_musics[1] = backgroundMusicMenu;

    lib->Explosion_effets[0] = explosion;
    
    lib->Laser_effets[0] = laser;

    lib->Selection_sounds[0] = select;
    lib->Selection_sounds[1] = winhealth;
    lib->Parry = parry;
}

void clean_Chunk(){
    Mix_ExpireChannel(0,0);
}

void clean_Music(){
    Mix_CloseAudio();
}

void play(sounds_t* sound,int loop){
    if (sound->type == CHUNK){
        Mix_PlayChannel(0,sound->chunk,loop);
    }else{
        Mix_PlayMusic(sound->music,loop);
    }
}

void control_sound(sounds_t* sound, int volume){
    if (sound->type == CHUNK){
        Mix_VolumeChunk(sound->chunk,volume);
    }else{
        Mix_VolumeMusic(volume);
    }
}


