/**
 * \file midi.h
 * \brief Midi functions
 *
 *
 * Here are defined the data structure of Midi data, and the relative function for works on midi data
 */
#include <stdio.h>
#include "../Listmidi/listmidi.h"
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
    u_int16_t MTHD[4]; /*!< 4 bytes for header flag*/
    u_int16_t SPEC_ADDR[4]; /*!< 4 bytes to inform about the addressing specs*/
    u_int16_t SMF ;/*!<2 bytes to indicate the data ranges: 0 only one data range, 1 several tracks played simultaneously, 2 more tracks but to be played one after the other*/
    u_int16_t MTRK ; /*!<2 bytes for the number of data ranges*/
    u_int16_t NOIRE; /*!< 2 bytes: number divisions of the black*/

} Header;
/*
typedef struct {
    u





}NOTE;
*/




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
 * \brief Function to read Data range from target file and record it in a buffer , this function read a file with readDataRangeSorted,setAsBeginDataRange,recordDataRange,getSizeDataRange
 *
 * \param file Target file to read midi data range
 *
 * \return buffer __uint32_t*  with the data range sorted
 */

//__uint32_t  * playDataRange (FILE *file);
/**
 * \fn __uint32_t  * readDataRangeSorted( u_int32_t size)
 * \brief Function read Data range and stock in buffer with size of data range
 *
 * \param size Size of the length of data
 * \param f midi File targeted for read
 *
 * \return buffer __uint32_t*  with the data range sorted
 */

__uint8_t  * readDataRange( u_int32_t sizeDataRange, FILE *file);
/**
 * \fn void setAsBeginDataRange (FILE *f)
 * \brief Function to go at the begining of  midi data ranged and passed it to begin the reading
 *
 * \param file Target midi File
 *
 */

void setAsBeginDataRange (FILE *file);
/**
 * \fn u_int32_t skipMetaData(FILE *file,u_int32_t size,u_int32_t currentLine)
 * \brief Function to ignore metaData in a data range
 *
 * \param file Target midi file
 * \param size length of the Data range to be read
 * \param currentLine Position for read in the File
 *
 * \return u_int32_t  currentLine
 */

u_int16_t getSizeMetaData(int i, u_int16_t * DataRange);
/**
 * \fn u_int32_t writeRomDataRange(FILE *f,u_int32_t size)
 * \brief Write Data Range sorted without Meta Data in a file tmp.txt, this function use  skipMetaData
 *
 * \param file Target File that contains data that wants to write in tmp.txt
 * \param size length of data Range
 *
 * \return u_int32_t length that write in tmp.txt
 */

u_int32_t writeRomDataRange(FILE *file,u_int32_t size);
/**
 * \fn u_int32_t getSizeDataRange(FILE *f)
 * \brief Function to know the length of midi Data Range
 *
 * \param file Target midi File
 *
 * \return length of data range
 */

u_int32_t getSizeDataRange(FILE *f);
/**
 * \fn playDataRange(u_int32_t DataRangeSorted)
 * \brief Function to know the length of midi Data Range
 *
 * \param
 * \param buffer_length The size of the audio buffer (number of audio samples in the buffer)
 * \param sample_rate The sample rate of the system
 * \param phase The phase value at the beginning of the buffer
 *
 * \return 0 if everything went OK, -1 otherwise
 */

void  sortDataRange(u_int8_t * DataRange, Header * H,u_int32_t sizeDataRange,list *l);

/**
 * \fn playDataRange(u_int32_t DataRangeSorted)
 * \brief Function to know the length of midi Data Range
 *
 * \param
 * \param buffer_length The size of the audio buffer (number of audio samples in the buffer)
 * \param sample_rate The sample rate of the system
 * \param phase The phase value at the beginning of the buffer
 *
 * \return 0 if everything went OK, -1 otherwise
 */

int * playDataRange (FILE  * test);
/**
 * \fn playDataRange(u_int32_t DataRangeSorted)
 * \brief Function to know the length of midi Data Range
 *
 * \param
 * \param buffer_length The size of the audio buffer (number of audio samples in the buffer)
 * \param sample_rate The sample rate of the system
 * \param phase The phase value at the beginning of the buffer
 *
 * \return 0 if everything went OK, -1 otherwise
 */

double calculDelay (__uint8_t * DataDelay, int power,u_int16_t Noire);



int readEvent (__uint8_t * midiNote, u_int8_t * attack, int  * midiEvent,u_int8_t * DataRange , int *  i);
#endif