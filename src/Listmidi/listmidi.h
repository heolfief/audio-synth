#include <stdio.h>
#ifndef LISTMIDI_H
#define LISTMIDI_H


typedef enum event event;

enum event {OFF_NOTE,ON_NOTE};







/*!
* \brief Une liste chaînée de note midi
*/

typedef struct {
    __uint8_t  midiNote;
    __uint8_t  attack;
   enum  event midiEvent;
    double delay;
    struct midiData * next;
}midiData;






typedef  struct {
  struct midiData * first;		/*!< L'adresse du premier élément de la liste */
  struct  midiData * current;		/*!< L'adresse de l'élément courant de la liste */
  struct midiData * last;
  double  accrued_delay;
  struct midiList * nextmidiList;

}midiList;







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

midiData * newNodeList(__uint8_t  *midiNote, __uint8_t *attack,  event  midiEvent, double  delay, midiData * next);

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
midiList * initList();

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
void printList(midiList * l);
/**
 * \fn int empty(list * l)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */
int empty(midiList * l);
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

int oneElement(midiList * l);
/**
 * \fn int count(list* l)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */
int count(midiList* l);

/**
 * \fn int first(list * l)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */
int first(midiList * l);

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
int isLast(midiList * l);

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
int isOutOfList(midiList * l);
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
void setOnFirst(midiList * l);
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
void setOnLast(midiList * l);
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
void next(midiList * l);
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

void* getCurrent(midiList * l);

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
int insertFirst(midiList * l, void* data);
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

int deleteFirst(midiList * l);
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

void freeNodeList(midiData * n);
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

void freeList(midiList * l);
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

int insertLast(midiList * l, void* data);

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
int deleteLast(midiList * l, void** data);

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

int insertAfterCurrent(midiList * l, void* data);
/**
 * \fn int deleteCurrent(list * l, void** data)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */



int deleteCurrent(midiList * l, void** data);




#endif