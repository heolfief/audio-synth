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
#include "../note/adsr.h"

#define print_error(s){fprintf(stderr, "%s : func %s at %s (%d)\n", s, __func__, __FILE__, __LINE__); }

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
    Uint16        freq;       /*!<the frequency of the note*/
    double        velocity_amp;/*!<the velocity / amplitude of the note (range from 0 to 1) */
    OnOff         onoff;      /*!<the on/off value of the note (MIDI protocol wise) */
    OnOff         master_onoff;/*!<the master on/off value of the note (including release time, when master_onoff is OFF, there is no sound from the note) */
    double        env_amp;    /*!<the envelope amplitude (range from 0 to 1) */
    Uint64        lifetime;   /*!<the number of samples passed since the note is ON (used to calculate envelope) */
    Uint64        deathtime;  /*!<the number of samples passed when note is OFF since the note was ON */
    Note_Buffer   buffer;     /*!<the audio data buffer of the note, resulting of the mix of the oscillators buffers */
}Note;

/**
 * \fn int note_on(Note *n)
 * \brief Function to turn on a note
 *
 * \param n The note structure
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int note_on(Note *n);

/**
 * \fn int note_off(Note *n)
 * \brief Function to turn off a note
 *
 * \param n The note structure
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int note_off(Note *n);

/**
 * \fn int note_fill_buffer(Note *n, Note_Buffer buffer, Uint16 buffer_length, const Envelope *env, Uint64 sample_rate, Uint64 phase)
 * \brief Function to fill note audio buffer with note data (mixed oscillators and envelope)
 *
 * \param n The note structure
 * \param buffer The audio buffer to write audio samples to
 * \param buffer_length The size of the audio buffer (number of audio samples in the buffer)
 * \param env The envelope parameters
 * \param sample_rate The sample rate of the system
 * \param phase The phase value at the beginning of the buffer
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int note_fill_buffer(Note *n, Note_Buffer buffer, Uint16 buffer_length, const Envelope *env, Uint64 sample_rate, Uint64 phase);

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
int update_envelope(Note *n, const Envelope *env);

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
