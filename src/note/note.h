/**
 * \file note.h
 * \brief Note data structure and function definition.
 *
 *
 * Here are defined the data structure of a note, and the related functions
 */

#ifndef AUDIO_SYNTH_NOTE_H
#define AUDIO_SYNTH_NOTE_H


#include <SDL2/SDL_stdinc.h>
#include "../oscillator/osc.h"

typedef Sint16 *Note_Buffer;


/**
 * \struct Note
 * \brief define a note
 *
 * A note is defined with : Oscillator 1, Oscillator 2, Oscillator 3, pitch, amplitude, on/off state, envelope and lifetime value
 * It is associated with it's own buffer to store the audio samples resulting of the mixed oscillators
 */
typedef struct{
    Oscillator*   osc1;       /*!<the first oscillator */
    Oscillator*   osc2;       /*!<the second oscillator */
    Oscillator*   osc3;       /*!<the third oscillator */
    Uint16        pitch;      /*!<the pitch / note*/
    Uint16        amp;        /*!<the amplitude of the note*/
    OnOff         onoff;      /*!<the on/off value of the note (MIDI protocol speaking)*/
    OnOff         master_onoff;/*!<the master on/off value of the note (including release time, when master_onoff is OFF, there is no sound from the note) */
    double        env_amp;    /*!<the envelope amplitude (range from 0 to 1) */
    Uint64        lifetime;   /*!<the number of samples passed since the note is ON (used to calculate envelope) */
    Uint64        deathtime;  /*!<the number of samples passed when note is OFF since the note was ON */
    Note_Buffer   buffer;     /*!<the audio data buffer of the note, resulting of the mix of the oscillators buffers */
}Note;

/**
 * \fn Note *alloc_note(Uint16 buff_nb_samples)
 * \brief Function to allocate memory for a note
 *
 * \param buff_nb_samples The number of samples in the audio buffer of the given note
 *
 * \return the allocated Note
 */
Note *alloc_note(Uint16 buff_nb_samples);

/**
 * \fn int free_osc(Note *note_to_free)
 * \brief Function to free memory of a note
 *
 * \param note_to_free The note to free
 *
 * \return 0
 */
int free_note(Note *note_to_free);

/**
 * \fn Note_Buffer alloc_note_buffer(Uint16 buff_nb_samples)
 * \brief Function to allocate memory for a note audio buffer
 *
 * \param buff_nb_samples The number of samples in the audio buffer
 *
 * \return the allocated Note_buffer
 */
Note_Buffer alloc_note_buffer(Uint16 buff_nb_samples);

/**
 * \fn int free_note_buffer(Note_Buffer note_buff)
 * \brief Function to free memory of a note audio buffer
 *
 * \param note_buff The note audio buffer
 *
 * \return 0
 */
int free_note_buffer(Note_Buffer note_buff);


#endif //AUDIO_SYNTH_NOTE_H
