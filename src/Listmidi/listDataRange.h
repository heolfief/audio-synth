//
// Created by vincent on 19/05/19.
//

#ifndef AUDIO_SYNTH_SRC_LISTMIDI_LISTDATARANGE_H_
#define AUDIO_SYNTH_SRC_LISTMIDI_LISTDATARANGE_H_
//
// Created by vincent on 19/05/19.
//
#include <stdio.h>
#include "listmidi.h"






typedef struct {
  struct midiList * first;		/*!< L'adresse du premier élément de la liste */
  struct  midiList * current;		/*!< L'adresse de l'élément courant de la liste */
  struct midiList * last;		/*!< L'adresse du dernier élément de la liste */
  int delay;
}dataRangeList;




/**
 * \fn midiList * newList(void * ptr, nodeList * next)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */

dataRangeList* newDataRange(int  delay, dataRangeList * next);

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
dataRangeList * initdataRangeList();

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
int emptyDataRange(dataRangeList * l);
/**
 * \fn int oneElement(list * l)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */



int firstDataRange(dataRangeList * l);

/**
 * \fn int last(list * l)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */
int LastDataRange(dataRangeList * l);

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
int OutOfDataRangeList(dataRangeList * l);
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
void setOnFirstDataRange(dataRangeList * l);
/**
 * \fn void setOnLast(list * l)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */
void setOnLastDataRange(dataRangeList * l);
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
void nextDataRange(dataRangeList * l);
/**
 * \fn void* getCurrent(list * l)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */

void* getCurrentDataRange(dataRangeList * l);

/**
 * \fn int insertFirst(list * l, void* data)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */
int insertFirstDataRange(dataRangeList * l, void* data);
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

int deleteFirstDataRange(dataRangeList * l);
/**
 * \fn void freeNodeList(nodeList * n)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */

void freemidiList(dataRangeList * n);
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

void freeDataRange(dataRangeList * l);
/**
 * \fn int insertLast(list * l, void* data)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */

int insertLastDataRange(dataRangeList * l, void* data);

/**
 * \fn int deleteLast(list * l, void** data)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */
int deleteLastDataRange(dataRangeList * l, void** data);

/**
 * \fn int insertAfterCurrent(list * l, void* data)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */



int deleteCurrentDataRange(dataRangeList * l, void** data);














#endif //AUDIO_SYNTH_SRC_LISTMIDI_LISTDATARANGE_H_
