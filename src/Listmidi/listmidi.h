#include <stdio.h>
#ifndef LISTMIDI_H
#define LISTMIDI_H
/**
 * \file listmidi.h
 * \brief Midi list functions
 *
 *
 * Here are defined the data structure of an event of midiData and midiList with the associated functions
 */
/**
 * \enum event
 * \brief define an event
 *
 * This enum is define with OFF_NOTE ON_NOTE
 */
typedef enum event event;

enum event
{
  OFF_NOTE, ON_NOTE
};

/**
 * \struct midiData
 * \brief define an Note
 *
 * This struct is define with midiNote, attack,midiEvent,delay,next
 */

typedef struct midiData
{
  __uint8_t midiNote;/*!< The midi Note to play */
  __uint8_t attack;/*!< The attack of the note  */
  enum event midiEvent;  /*!< The event */
  double delay;  /*!< Delay to wait before this event*/
  struct midiData *next; /*!< The next midiData*/
} midiData;

/**
 * \struct midiList
 * \brief define an linked list of midiData
 *
 * This struct is define with first,current,last,accrued_delay,nextmidiList
 */
typedef struct midiList
{
  struct midiData *first;        /*!< The first midiData in the list */
  struct midiData *current;        /*!< The current midiData in the list */
  struct midiData *last;            /*!< The last midiData in the list*/
  double accrued_delay;           /*!< The accrued delay of all note read before*/
  struct midiList *nextmidiList;   /*!< The next midiList*/

} midiList;

/**
 * \fn fill_midiData(__uint8_t midiNote, __uint8_t attack, event midiEvent, double delay, midiData *current)
 * \brief Function to fill an midiData struct
 *
 * \param midiNote The midi Note to play
 * \param attack the attack of the selected note
 * \param midiEvent The event associated with the selected note
 * \param delay The delay before this note has played
 * \param midiData The current midiData to know the next midiData
 *
 */
void fill_midiData(__uint8_t midiNote, __uint8_t attack, event midiEvent, double delay, midiData *current);
/**
 * \fn new_note_list(__uint8_t midiNote, __uint8_t attack, event midiEvent, double delay, midiData *previous)
 * \brief Function to allocate a new node
 *
 * \param midiNote The midi Note to play
 * \param attack the attack of the selected note
 * \param midiEvent The event associated with the selected note
 * \param delay The delay before this note has played
 * \param previous The current midiData to know the next midiData
 *

 * \return An Struct midiData filled
 */

midiData *new_note_list(__uint8_t midiNote, __uint8_t attack, event midiEvent, double delay, midiData *previous);

/**
 * \fn void initList()
 * \brief Function to init a midiList with an allocation
 *
 *
 * \return an midiList allocated
 */
midiList *initList();

/**
 * \fn int empty(list * l)
 * \brief Function to know if a list is empty or not
 *
 * \param l The midiList to test

 *
 * \return 1 if the list was empty 0 otherwise
 */
int empty(midiList *l);

/**
 * \fn first(midiList * l)
 * \brief Function to know if the element was the first
 *
 * \param l The midiList

 *
 * \return 1 if the current was the fist in the midiList 0 otherwise
 */
int first(midiList *l);

/**
 * \fn int outOfList(list * l)
 * \brief Function to know if the current element of the list is Out of list
 *
 * \param l The midiList

 *
 * \return 1 if the current was Out of the list  in the midiList 0 otherwise
 */
int isOutOfList(midiList *l);
/**
 * \fn void setOnFirst(list * l)
 * \brief Function to put the current element of a midiList to the first
 *
 * \param l The midiList with the current to put at first


 */
void setOnFirst(midiList *l);

/**
 * \fn void next(list * l)
 * \brief Function to put the current element of a midi list to the next element
 *
 \param l The midiList with the current to next
 */
void next(midiList *l);

/**
 * \fn int deleteFirst(midiList * l)
 * \brief Function to delete the first element of the list
 *
 \param l The midiList with the current to next
 *
 * \return 1 if the first element was deleted  in the midiList 0 otherwise
 */

int deleteFirst(midiList *l);
/**
 * \fn void freeNodeList(nodeList * n)
 * \brief Function to free an node of the list in our case a midiData
 *
 * \param n the selected midiData to delete


 */

void freeNodeList(midiData *n);
/**
 * \fn void freeList(list * l)
 * \brief Function to free a midiList
 *
 \param l The midiList to delete
 */

void freeList(midiList *l);

#endif