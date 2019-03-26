/**
 * \file polyphony.h
 * \brief Polyphony data structure and function definition.
 *
 *
 * Here are defined the data structure of polyphony, and the related functions
 */

#ifndef AUDIO_SYNTH_POLYPHONY_H
#define AUDIO_SYNTH_POLYPHONY_H

#include <SDL2/SDL_stdinc.h>
#include "../note/note.h"
#include "../system/error_handler.h"

#define POLYPHONY_MAX 100

typedef Note*   Polyphony;    // Polyphony is an array of Note
typedef Sint16* Audio_Buffer;

/**
 * \fn int find_free_note(Polyphony *p)
 * \brief Function to find a note which is not used (=OFF) in Polyphony
 *
 * \param p The Polyphony array
 *
 * \return The index of the note in the Polyphony array if found, -1 otherwise
 */
int find_free_note(Polyphony *p);

/**
 * \fn int polyphony_fill_buffer(Polyphony *p, Uint16 buffer_length, const Envelope *env, Uint64 sample_rate, Uint64 phase)
 * \brief Function to fill Polyphony array audio buffer with all the notes buffers.
 *
 * Volume of each note depends on the number of active notes, to keep audio amplitude within the data range
 *
 * \param audio_buff The master audio buffer (all notes mixed)
 * \param p[] The Polyphony array
 * \param buffer_length The size of the audio buffer (number of audio samples in the buffer)
 * \param env The envelope parameters
 * \param sample_rate The sample rate of the system
 * \param phase The phase value at the beginning of the buffer
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int polyphony_fill_buffer(Audio_Buffer audio_buff, Polyphony *p, Uint16 buffer_length, const Envelope *env, Uint64 sample_rate, Uint64 phase);

/**
 * \fn int alloc_polyphony(Polyphony p, Uint16 buff_nb_samples)
 * \brief Function to allocate memory for Polyphony array
 *
 * \param buff_nb_samples The number of samples in the audio buffer of the notes
 *
 * \return The allocated polyphony array
 */
Polyphony *alloc_polyphony(Uint16 buff_nb_samples);

/**
 * \fn int free_polyphony(Polyphony *p)
 * \brief Function to free memory of a polyphony
 *
 * \param p The polyphony array to free
 *
 * \return 0
 */
int free_polyphony(Polyphony *p);

/**
 * \fn Note_Buffer alloc_audio_buffer(Uint16 buff_nb_samples)
 * \brief Function to allocate memory for a note audio buffer
 *
 * \param buff_nb_samples The number of samples in the audio buffer
 *
 * \return the allocated Audio_buffer
 */
Audio_Buffer alloc_audio_buffer(Uint16 buff_nb_samples);

/**
 * \fn int free_audio_buffer(polyphony_Buffer note_buff)
 * \brief Function to free memory of a polyphony audio buffer
 *
 * \param note_buff The audio buffer
 *
 * \return 0
 */
int free_audio_buffer(Audio_Buffer audio_buff);

#endif //AUDIO_SYNTH_POLYPHONY_H