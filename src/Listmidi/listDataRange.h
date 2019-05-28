

/**
 * \file listDataRange.h
 * \brief list dataRange function
 *
 *
 * Here are defined the function that works data range list
 */



#ifndef AUDIO_SYNTH_SRC_LISTMIDI_LISTDATARANGE_H_
#define AUDIO_SYNTH_SRC_LISTMIDI_LISTDATARANGE_H_

#include <stdio.h>
#include "listmidi.h"

/**
 * \struct dataRangeList
 *
 * \brief define linked list data range list with a linked list of midi list
 *
 * This struct is define with first data range current data range last data range
 */



typedef struct dataRangeList
{
  struct midiList *firstDataRange;        /*!< L'adresse du premier élément de la liste */
  struct midiList *currentDataRange;      /*!< L'adresse de l'élément courant de la liste */
  struct midiList *lastDataRange;        /*!< L'adresse du dernier élément de la liste */
} dataRangeList;


/**
 * \fn updateDelayDataRange(dataRangeList *l)
 * \brief Function to update all delay in all midi list
 * \param l data range list to update

 *
 * \return data range list updated
 */


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
/**
 * \fn getCount(dataRangeList *l)
 * \brief Function to count the element stored in data range list
 *
 * \param l data range list to count

<<<<<<< HEAD
 *
 * \return the number of of element stored
 */

int getCount(dataRangeList *l);

#endif