/**
 * \file listDataRange.h
 * \brief BRIEF DESCRIPTION
 *
 *  DESCRIPTION
 */

#ifndef AUDIO_SYNTH_SRC_LISTMIDI_LISTDATARANGE_H_
#define AUDIO_SYNTH_SRC_LISTMIDI_LISTDATARANGE_H_

#include <stdio.h>
#include "listmidi.h"
#include "stdio.h"
#include "stdlib.h"
#include "../core/note/adsr.h"
#include "listmidi.h"

// DOXYGEN
typedef struct dataRangeList
{
  struct midiList *firstDataRange;        /*!< L'adresse du premier élément de la liste */
  struct midiList *currentDataRange;        /*!< L'adresse de l'élément courant de la liste */
  struct midiList *lastDataRange;        /*!< L'adresse du dernier élément de la liste */
} dataRangeList;

// DOXYGEN
dataRangeList *updateDelayDataRange(dataRangeList *l);

/**
 * \fn midiList * newList(void * ptr, nodeList * next)
 * \brief Function to open a target File
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */
midiList *new_Midi_List(midiList *current, midiList *previous);

/**
 * \fn void initList(list * l)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */
dataRangeList *initdataRangeList();

/**
 * \fn void printList(list * l)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */
int emptyDataRange(dataRangeList *l);

/**
 * \fn int outOfList(list * l)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */
int OutOfDataRangeList(dataRangeList *l);

/**
 * \fn void setOnFirst(list * l)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */
void setOnFirstDataRange(dataRangeList *l);

/**
 * \fn void next(list * l)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */
void nextDataRange(dataRangeList *l);

/**
 * \fn int deleteFirst(list * l, void** data)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */
int deleteFirstDataRange(dataRangeList *l);

/**
 * \fn void freeList(list * l)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */
void freeDataRange(dataRangeList *l);

/**
 * \fn void freeList(list * l)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */
midiData *getFirstNoteToPlay(dataRangeList *l);

// DOXYGEN
int getCount(dataRangeList *l);

#endif