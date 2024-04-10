#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef enum {
    CHUNK, /** type chunk */
    MUSIC /** type music */
} sound_type;

/**
 * \brief Structure d'un son.
 */

struct sounds{
    const char* S_name; /** Nom du son */
    sound_type type; /** Type : chunk ou music */
    Mix_Chunk *chunk; /** adresse du chunk */
    Mix_Music *music; /** adresse de la musique */
    
};

/**
 * \brief Type qui correspond aux sons utilisés dans le jeu.
 */

typedef struct sounds sounds_t;

/**
 * \brief Structure bibliothèque des sons.
 */

struct Sounds_library{
    sounds_t Background_musics[5];
    sounds_t Explosion_effets[5];
    sounds_t Laser_effets[5];
    sounds_t Selection_sounds[5];
    sounds_t Parry;
};

/**
 * \brief 
 */

typedef struct Sounds_library Sounds_lib_t;

/**
 * \brief La fonction initialise le mixer.
 * Elle permet de lancer des musiques et des chunks.
*/

void init_mixer();

 /**
 * \brief La fonction qui initialise les sons.
 * La structure consiste en une bibliothèque où on récupère les sons.
 *  \param lib la structure bibliothèque.
*/

void init_sons(Sounds_lib_t * lib);

 /**
 * \brief La fonction qui nettoie les chunks(format).
 * Permet de nettoyer efficacement les chunks dans le channel (voir doc en ligne).
*/
void clean_Chunk();

 /**La fonction qui nettoie les musiques(format).
 * Permet de nettoyer efficacement les musiques dans le channel (voir doc en ligne).
*/
void clean_Music();

 /**
 * \brief La fonction qui joue le son.
 * C'est la fonction la plus importante et la plus facile à utiliser.
 * Elle est plug and play, il y a juste à choisir un son dans la structure et combien de fois on veut répéter ce son.
*/
void play(sounds_t* sound,int loop);

 /**
 * \brief La fonction gère le volume.
 * Modifie le volume sonore du chunk en question
*/
void control_sound(sounds_t* sound, int volume);
