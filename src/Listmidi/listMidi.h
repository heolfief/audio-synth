#include <stdio.h>

#ifndef LISTMIDI_H
#define LISTMIDI_H


/*!
* \brief Une liste chaînée d'éléments génériques (void*)
*/
typedef struct {
    nodeList * first;		/*!< L'adresse du premier élément de la liste */
    nodeList * current;		/*!< L'adresse de l'élément courant de la liste */
    nodeList * last;		/*!< L'adresse du dernier élément de la liste */
}list;



nodeList * newNodeList(void * ptr, nodeList * next, nodeList * previous);


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