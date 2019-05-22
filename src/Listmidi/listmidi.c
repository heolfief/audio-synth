#include <stdio.h>
#include "listmidi.h"
#include <stdlib.h>




midiData * new_note_list(__uint8_t midiNote, __uint8_t attack, event midiEvent, double delay, midiData *previous)
{
    midiData * new = (midiData*)malloc(sizeof(midiData));  /*Allocation de l'espace mmoire*/
    if (new == NULL)
    {
        fprintf(stderr, "Warning/error : allocation mmoire dynamique chou dans la fonction %s\n", __FUNCTION__);
        return NULL;		/*L'allocation  chou*/
    }

    new->midiNote = midiNote;
    new->midiEvent= midiEvent;
    new->attack= (u_int8_t ) attack;
    new->delay = delay;
    previous->next = (struct midiData * ) new;
    new->next = NULL;
    return new;				/*Return du pointeur vers la node cre*/
}



midiList *  initList()
{
    midiList * l = NULL;

    l = (midiList*) malloc(sizeof(midiList));
    if (l == NULL)
    {
        fprintf(stderr, "Warning/error : allocation memoire dynamique chou dans la fonction %s\n", __FUNCTION__);
        return NULL;		/*L'allocation  chou*/
    }
    l->current= NULL;
    l->first = NULL;

    l->current = (struct midiData*) malloc(sizeof(midiData));
    l->first =   l->current;
    l->last = NULL;
    l->accrued_delay =0;
    l->nextmidiList = NULL;
    return l ;


}


void freeList(midiList* l){
    while(!empty(l)) deleteFirst(l);



}

void freeNodeList(midiData *n){
    if (n!=NULL)
        free(n);


}

void setOnFirst(midiList *l){
    l->current = l->first;
}



int deleteFirst(midiList *l){
    if (empty(l))
            return 0;
    midiData * toDel = ( midiData * )l->first;
    l->first = l->first->next;
    freeNodeList(toDel);
    if (empty(l))
    {
        l->last = NULL;

    }
    setOnFirst(l);
    return 1;

}

int count(midiList* l)
{
    int count =0;
    for(setOnFirst(l); !isOutOfList(l) ; next(l))
        count++;
    return count;
}

void next(midiList* l)
{
    if(isOutOfList(l))
        return;
      midiData *n ;
     n=(midiData*)l->current;
    l->current = n->next;
}

int isOutOfList(midiList* l)
{
    return l->current == NULL;
}


void setOnLast(midiList* l)
{
    l->current = l->last;
}




int isLast(midiList* l)
{
return l->current == l->last && l->current != NULL;
}


int empty(midiList * l)
{
    return (l->first == NULL);
}

int oneElement(midiList * l)
{
    return (l->first != NULL && l->first == l->last);
}

void printList(midiList * l)
{
    midiData* n;
    printf("{");
    n =(midiData*) l->first;
    while (n != NULL)
    {
        printf(" Midi event : %d  Delay : %f  Midi note : %2x attack : %2x \n ", n->midiEvent, n->delay, n->midiNote,n->attack);

        n = (midiData*) n->next;
    }
    freeNodeList(n);
    printf("}\n");
}

