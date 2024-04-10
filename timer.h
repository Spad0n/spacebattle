#ifndef TIMER_H
#define TIMER_H

#include "entities.h"

/**
 * \brief La fonction qui initialise des callbacks dans le jeu
 * \param world les données du monde
 */

void time_event_start(world_t* world);

/**
 * \brief La fonction qui change le déplacement des ennemis aléatoire
 * \param interval pour affecter le nombre de ticks pour relancer l'evenement
 * \param param pour affecter les paramètre
 * \return le nombre d'interval
 */

unsigned int random_move(unsigned int interval, void* param);

/**
 * \brief La fonction qui change l'etat d'un ennemi après avoir tiré
 * \param interval pour affecter le nombre de ticks pour relancer l'evenement
 * \param param pour affecter les paramètre
 * \return le nombre d'interval
 */

unsigned int shooting_state(unsigned int interval, void* param);

/**
 * \brief La fonction qui change l'état d'un ennemi
 * \param interval pour affecter le nombre de ticks pour relancer l'evenement
 * \param param pour affecter les paramètre
 * \return le nombre d'interval
 */

unsigned int change_state(unsigned int interval, void* param);

/**
 * \brief La fonction qui met en pause après que le joueur a nettoyé complètement les ennemis
 * \param interval pour affecter le nombre de ticks pour relancer l'evenement
 * \param param pour affecter les paramètre
 * \return le nombre d'interval
 */

unsigned int wave_clear(unsigned int interval, void* param);

#endif
