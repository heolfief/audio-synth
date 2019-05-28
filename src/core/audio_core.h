/**
 * \file audio_core.h
 * \brief Audio core functions definition.
 *
 *
 * Here are defined the audio core, which contains sound synthesis and effects
 */

#ifndef AUDIO_SYNTH_AUDIO_CORE_H
#define AUDIO_SYNTH_AUDIO_CORE_H

#include <SDL2/SDL_stdinc.h>
#include <sndfile.h>
#include "../sys_param/sys_param.h"
#include "../system/error_handler.h"
#include "note/polyphony.h"
#include "../audio_fx/audio_fx.h"

/**
 * \struct RecordParam
 * \brief defines the Recording info for the audio core
 *
 * The parameters are : a Onoff switch indicating if we need to record and the sound file to record to
 */
typedef struct
{
  OnOff RecordOnOff;                  /*!< flag if a wav file is being recorded*/
  SNDFILE *sndFile;                   /*!< the "sndfile" being recorded*/
} RecordParam;

typedef struct
{
  OnOff Midi_file_opened;             /*!< flag is a midi file is open*/
  OnOff Midi_playing_OnOff;           /*!< flag if a midi file is being played*/
  OnOff Midi_paused_file;             /*!< flag if a midi file is paused*/
  OnOff Midi_stopped_file;            /*!< flag if a midi file is stopped and closed*/
  const char *Midi_file_Path;         /*!< path of the file to be played*/
}MidiParam;
/**
 * \struct Core
 * \brief define an audio core
 *
 * An audio core consists of a buffer containing final audio data to be played by the soundcard, the system parameters,
 * the polyphony array of the system and the phase of the system.
 */
typedef struct
{
  Polyphony *note_array;             /*!<the polyphony array of the system */
  Audio_Buffer master_audio;         /*!<the master audio buffer */
  Sys_param *sys_param;              /*!<the system parameters */
  Uint64 phase;                      /*!<the phase of the oscillators */
  Effect_core *effect_core;          /*!<the structure containing effect related objects */
  Audio_Buffer average_audio_level;  /*!<the average instantaneous volume level that is played by the soundcard */
  Uint8 buffer_is_new;               /*!<flag if the buffer is refilled*/
  RecordParam *record_param;          /*!< structure containing recording parameters*/
  MidiParam *midi_param;              /*!< structure containing midi playing parameters*/
} Core;

/**
 * \fn Core alloc_core()
 * \brief Allocate an audio core
 *
 * \param buffer_length The size of the audio buffer (number of audio samples in the buffer)
 *
 * \return The allocated Core
 */
Core *alloc_core(Uint16 buffer_length);

/**
 * \fn int free_core(Core* ac)
 * \brief Function to free audio core memory
 *
 * \param ac The audio core structure of the system
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int free_core(Core *ac);

/**
 * \fn int synthesis_fill_buffer(Core* ac)
 * \brief Function to fill master audio buffer with audio synthesis
 *
 * \param ac The audio core structure of the system
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int synthesis_fill_buffer(Core *ac);

/**
 * \fn int master_audio_fill_buffer(Core* ac)
 * \brief Function to fill master audio buffer with audio synthesis and effects
 *
 * \param ac The audio core structure of the system
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int master_audio_fill_buffer(Core *ac);

/**
 * \fn int master_effects(Core* ac)
 * \brief Function to apply effects to master audio buffer
 *
 * \param ac The audio core structure of the system
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int master_effects(Core *ac);

/**
 * \fn Sint16 moving_average(Sint16 sample)
 * \brief Performs the moving average of a stream of audio samples
 *
 * \param sample new sample to take account in the average calculation
 *
 * \return the actual average
 */
Sint16 moving_average(Sint16 sample);

/**
 * \fn int free_record_param(RecordParam *record_param)
 * \brief free the recording parameters of the audio core
 *
 * \param recording parameters
 *
 * \return 0 if went well
 */
int free_record_param(RecordParam *record_param);

/**
 * \fn int free_midi_param(MidiParam *midi_param)
 * \brief free the midi playing parameters of the audio core
 *
 * \param midi parameters
 *
 * \return 0 if went well
 */
int free_midi_param(MidiParam *midi_param);


#endif //AUDIO_SYNTH_AUDIO_CORE_H
