/**
 * \file midi.h
 * \brief Midi functions
 *
 *
 * Here are defined the data structure of Midi data, and the relative function for works on midi data
 */
#include <stdio.h>
#include "../Listmidi/listmidi.h"
#include "../Listmidi/listDataRange.h"
#include "../core/audio_core.h"
#ifndef MIDI_H
#define MIDI_H
#define MSKHEX 0xF0
#define MSKBIN 0x80



/**
 * \struct Header
 * \brief define an header of a midi file
 *
 * This struct is define with MTHD, SPEC_ADDR,SMF,MTRK,NOIRE
 */

typedef struct {
    __uint16_t MTHD[4]; /*!< 4 bytes for header flag*/
  __uint16_t SPEC_ADDR[4]; /*!< 4 bytes to inform about the addressing specs*/
  __uint16_t SMF ;/*!<2 bytes to indicate the data ranges: 0 only one data range, 1 several tracks played simultaneously, 2 more tracks but to be played one after the other*/
  __uint16_t MTRK ; /*!<2 bytes for the number of data ranges*/
  __uint16_t NOIRE; /*!< 2 bytes: number divisions of the black*/
} Header;


/**
 * \fn void fillHeaderRead (Header*H, FILE* f)
 * \brief Function to fill an midi header from a target file
 *
 * \param Header Header struct to fill
 * \param file Target File
 *
 * \return error if file is not a midi file
 */

void fillHeaderRead (Header*Header, FILE* file);
/**
 * \fn __uint32_t  *readDataRange (FILE *f)
 * \brief Function to read Data range from target file and record it in a buffer.
 *
 * \param file Target file to read midi data range
 * \param sizeDataRange size of the data range
 *
 * \return buffer __uint8_t*  with the data range of a midi file
 */


__uint8_t  * readDataRange( __uint32_t sizeDataRange, FILE *file);
/**
 * \fn void setAsBeginDataRange (FILE *f)
 * \brief Function to go at the begining of  midi data ranged and passed it to begin the reading
 *
 * \param file Target midi File
 *
 */

void setAsBeginDataRange (FILE *file);

/**
 * \fn u_int32_t getSizeDataRange(FILE *f)
 * \brief Function to know the length of midi Data Range
 *
 * \param file Target midi File
 *
 * \return length of data range
 */

__uint32_t getSizeDataRange(FILE *f);
/**
 * \fn sorDataRange(u_int32_t DataRangeSorted)
 * \brief Function to sort all the event of a data range
 *
 * \param DataRange buffer with the dataRange from midi File
 * \param H Header information  of the midi file
 * \param sizeDataRange size of the data Range
 * \param l The midiist to fill with the data range sorted
 *

 */

void  sortDataRange(__uint8_t* DataRange, Header * H,__uint32_t sizeDataRange,midiList *l);


/**
 * \fn calculDelay (__uint8_t * DataDelay, int power,__uint16_t Noire)
 * \brief Function to calcul th delay betwen two events, with conversion of hexadecimal into decimal
 *
 * \param DataDelay An array with the data of delay in hex
 * \param power_rate The power of hexadecimal data
 * \param Noire The time indicator to know how divide the time
 *
 * \return the resultat of the operation
 */

double calculDelay (__uint8_t * DataDelay, int power,__uint16_t Noire);

/**
 * \fn readEvent (__uint8_t * midiNote, __uint8_t * attack, int  * midiEvent,__uint8_t* DataRange , int *  i)
 * \brief Function to sort the kind of event
 *
 * \param midiNote The struct to fill
 * \param attack the attack of the note
 * \param midiEvent the kind of event Note on or Note off
 * \param DataRange The array with all data from the midi File
 * \param i The incrementation in the DataRange array
 *
 * \return the incrementation in the arrey DataRange
 */


int readEvent (__uint8_t * midiNote, __uint8_t * attack, int  * midiEvent,__uint8_t* DataRange , int *  i);
/**
 * \fn record_midi_file(char * name)
 * \brief Function to record in dataRangeList all the midilist with the note of a midi File
 *
 * \param name the path of the targeted file
 *
 * \return the dataRangelist filled with all data of midi file
 */

dataRangeList * record_midi_file(char * name);


/**
 * \fn playMidiFile(Core * audio_core, double currentTime,dataRangeList * l,int size)
 * \brief Function to play  song with a dataRange List
 *
 * \param audio_core the core of the application
 * \param currentTime the tima has passed from the moment that application started
 * \param l_the data range with all the data
 * \param size the number of data Range
 *

 */


void playMidiFile(Core * audio_core, double currentTime,dataRangeList * l,int size);

/**
 * \fn controlMidi (double currenTime,Core * ac )
 * \brief Function to control the midi reading with the different flags from gui
 *
 * \param ac core the core of the application
 * \param currenTime he tima has passed from the moment that application started
 */


void controlMidi (double currenTime,Core * ac );



#endif