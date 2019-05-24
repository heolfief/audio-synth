#include <stdio.h>
#include "listmidi.h"
#include "../core/note/adsr.h"
#include <stdlib.h>




midiData * new_note_list(__uint8_t midiNote, __uint8_t attack, event midiEvent, double delay, midiData *previous)
{
    midiData * new = (midiData*)malloc(sizeof(midiData));
    if (new == NULL)
    {
        sys_print_error("error new node list malloc");
        return NULL;
    }
    fill_midiData(midiNote,attack,midiEvent,delay,new);

        new->next = (midiList*) previous;


    return new;
}


void fill_midiData(__uint8_t midiNote, __uint8_t attack, event midiEvent, double delay, midiData *current){

    current->midiNote = midiNote;
    current->midiEvent= midiEvent;
    current->attack= (u_int8_t ) attack;
    current->delay = delay;



}



midiList * initList()
{
    midiList * l = (midiList*) malloc(sizeof(midiList));
    if (l == NULL)
    {
        sys_print_error("initialisation midi list is NULL");

    }
   l->accrued_delay = 0;
    l->current = NULL;
    l->first= NULL;
    l->last = NULL;
    return  l;
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
    if (l==NULL)
        return 1;
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

