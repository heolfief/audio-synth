#include <stdio.h>
#ifndef LISTMIDI_H
#define LISTMIDI_H


typedef enum event event;

enum event {OFF_NOTE,ON_NOTE};



typedef struct {
    __uint8_t  midiNote;
    __uint8_t  attack;
   enum  event midiEvent;
    double delay;
    struct midiList * next;
}midiList;


/*!
* \brief Une liste chaînée d'éléments génériques (void*)
*/
typedef struct {
    struct midiList * first;		/*!< L'adresse du premier élément de la liste */
    struct  midiList * current;		/*!< L'adresse de l'élément courant de la liste */
    struct midiList * last;		/*!< L'adresse du dernier élément de la liste */
}list;

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

midiList * newNodeList(__uint8_t  *midiNote, __uint8_t *attack,  event  midiEvent, double  delay, midiList * next);

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
list * initList();

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
void printList(list * l);
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
int empty(list * l);
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

int oneElement(list * l);
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
int count(list* l);

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
int first(list * l);

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
int isLast(list * l);

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
int isOutOfList(list * l);
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
void setOnFirst(list * l);
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
void setOnLast(list * l);
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
void next(list * l);
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

void* getCurrent(list * l);

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
int insertFirst(list * l, void* data);
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

int deleteFirst(list * l);
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

void freeNodeList(midiList * n);
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

void freeList(list * l);
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

int insertLast(list * l, void* data);

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
int deleteLast(list * l, void** data);

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

int insertAfterCurrent(list * l, void* data);
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



int deleteCurrent(list * l, void** data);




#endif