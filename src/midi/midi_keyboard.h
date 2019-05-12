/**
 * \file midi.h
 * \brief MIDI functions definition.
 *
 *
 * Here are defined the MIDI related function, for both MIDI files and USB MIDI (from keyboard)
 */

#ifndef AUDIO_SYNTH_SRC_MIDI_MIDI_KEYBOARD_H_
#define AUDIO_SYNTH_SRC_MIDI_MIDI_KEYBOARD_H_

#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_stdinc.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../system/error_handler.h"
#include "../core/audio_core.h"

// Defines the number of known MIDI devices in /dev/
#define NUMBER_OF_KNOWN_MIDI_DEV 11

#define MIDI_NOTE_0_FREQ 8.1757989156
#define MAX_MIDI_NOTE_VELOCITY 127.0

typedef int MIDI_Peripheral_fd;

/**
 * \fn MIDI_PERIPHERAL* open_midi_peripheral()
 * \brief Function to open a MIDI peripheral as FILE*.
 *
 * It search for available midi device in "/dev/"
 *
 * \return the file descriptor to the midi peripheral file, or NULL if not found
 */
MIDI_Peripheral_fd open_midi_peripheral();

/**
 * \fn int process_midi_input(MIDI_PERIPHERAL* mp, Core* ac)
 * \brief Function to process MIDI input from the opened MIDI peripheral and set the audio core to create notes associated with MIDI input
 *
 * \param mp The midi peripheral file descriptor address
 * \param ac The audio core structure of the system
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int process_midi_input(MIDI_Peripheral_fd* mp, Core *ac);

/**
 * \fn int midi_note_ON(Core *ac, Uint8 id, Uint8 velo)
 * \brief Function to process MIDI input from the opened MIDI peripheral and set the audio core to create notes associated with MIDI input
 *
 * \param ac The audio core structure of the system
 * \param id the note ID aka MIDI note number
 * \param velo the note velocity (range from 1 to 127)
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int midi_note_ON(Core *ac, Uint8 id, Uint8 velo);

/**
 * \fn int midi_note_OFF(Core *ac, Uint8 id)
 * \brief Function to process MIDI input from the opened MIDI peripheral and set the audio core to create notes associated with MIDI input
 *
 * \param ac The audio core structure of the system
 * \param id the note ID aka MIDI note number
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int midi_note_OFF(Core *ac, Uint8 id);

/**
 * \fn int close_midi_peripheral(MIDI_PERIPHERAL *mp)
 * \brief Function to close  a MIDI peripheral
 *
 * \param fd The MIDI peripheral fd (file descriptor) to close
 *
 * \return 0
 */
int close_midi_peripheral(MIDI_Peripheral_fd fd);

#endif //AUDIO_SYNTH_SRC_MIDI_MIDI_KEYBOARD_H_
