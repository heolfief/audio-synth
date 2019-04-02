#include <stdio.h>

#ifndef LISTMIDI_H
#define LISTMIDI_H


typedef enum event {ON, OFF};



typedef struct midiList{
    __uint16_t  midiNote;
    __uint16_t  attack;
    event midiEvent;
    __uint32_t delay;
    struct midiList * next;
};


/*!
* \brief Une liste chaînée d'éléments génériques (void*)
*/
typedef struct {
    midiList * first;		/*!< L'adresse du premier élément de la liste */
    midiList * current;		/*!< L'adresse de l'élément courant de la liste */
    midiList * last;		/*!< L'adresse du dernier élément de la liste */
}list;



midiList * newList(void * ptr, nodeList * next, nodeList * previous);


void initList(list * l);


void printList(list * l);

int empty(list * l);


int oneElement(list * l);

int count(list* l);


int first(list * l);


int last(list * l);


int outOfList(list * l);

void setOnFirst(list * l);

void setOnLast(list * l);

void next(list * l);

void previous(list * l);


void* getCurrent(list * l);


int insertFirst(list * l, void* data);


int deleteFirst(list * l, void** data);


void freeNodeList(nodeList * n);


void freeList(list * l);


int insertLast(list * l, void* data);


int deleteLast(list * l, void** data);



int insertAfterCurrent(list * l, void* data);



int insertBeforeCurrent(list * l, void* data);


int deleteCurrent(list * l, void** data);





#endif