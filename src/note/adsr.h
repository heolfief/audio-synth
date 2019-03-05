/**
 * \file note.h
 * \brief ADSR envelope filter data structure and function definition.
 *
 *
 * Here are defined the data structure of an ADSR envelope filter, and the related functions
 */

#ifndef AUDIO_SYNTH_ADSR_H
#define AUDIO_SYNTH_ADSR_H

#include <SDL2/SDL_stdinc.h>
#include "../note/note.h"

/**
 * \struct Envelope
 * \brief define an ADSR envelope
 *
 * An ADSR envelope is defined with four parameters : attack, decay, sustain, release
 */
typedef struct{
    Uint64        attack;        /*!<the time for initial run-up of level from nil to peak in sample */
    Uint64        decay;         /*!<the time for the subsequent run down from the attack level to the designated sustain level in samples */
    double        sustain;       /*!<the level during the main sequence of the sound's duration, until the note is off (range from 0 to 1)*/
    Uint64        release;       /*!<the time taken for the level to decay from the sustain level to zero after the note is off in samples*/
}Envelope;

/**
 * \fn int update_envelope(Note *n, Envelope *env)
 * \brief Function to compute and update envelope amplitude based on an ADSR envelope filter
 *
 * Works on a sample, not a buffer.
 *
 * \param n The note object to update envelope to
 * \param env The envelope object
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int update_envelope(Note *n, Envelope *env);

#endif //AUDIO_SYNTH_ADSR_H
