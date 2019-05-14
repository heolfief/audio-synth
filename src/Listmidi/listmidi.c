#include <stdio.h>
#include "listmidi.h"
#include <stdlib.h>




midiList * newNodeList(__uint8_t * midiNote, __uint8_t *attack,   event  midiEvent, double delay, midiList * previous)
{
    midiList * new = (midiList*)malloc(sizeof(midiList));  /*Allocation de l'espace mmoire*/
    if (new == NULL)
    {
        fprintf(stderr, "Warning/error : allocation mmoire dynamique chou dans la fonction %s\n", __FUNCTION__);
        return NULL;		/*L'allocation  chou*/
    }

    new->midiNote = midiNote;
    new->midiEvent= midiEvent;
    new->attack= attack;
    new->delay = delay;
    previous->next = new;
    new->next = NULL;
    return new;				/*Return du pointeur vers la node cre*/
}



list *  initList()
{
    list * l =NULL;
    l = (list*) malloc(sizeof(list));
    if (l == NULL)
    {
        fprintf(stderr, "Warning/error : allocation memoire dynamique chou dans la fonction %s\n", __FUNCTION__);
        return NULL;		/*L'allocation  chou*/
    }

    l->current = (midiList*) malloc(sizeof(midiList));
    l->first =   l->current;
    l->last = NULL;

    return l ;


}


void freeList(list* l){
    while(!empty(l)) deleteFirst(l);



}

void freeNodeList(midiList *n){
    if (n!=NULL)
        free(n);


}

void setOnFirst(list *l){
    l->current = l->first;
}



int deleteFirst(list *l){
    if (empty(l))
            return 0;
    midiList * toDel = l->first;
    l->first = toDel->next;
    freeNodeList(toDel);
    if (empty(l))
    {
        l->last = NULL;

    }
    setOnFirst(l);
    return 1;

}

int count(list* l)
{
    int count =0;
    for(setOnFirst(l); !isOutOfList(l) ; next(l))
        count++;
    return count;
}

void next(list* l)
{
    if(isOutOfList(l))
        return;
    midiList *n ;
    n=l->current;
    l->current = n->next;
}

int isOutOfList(list* l)
{
    return l->current == NULL;
}


void setOnLast(list* l)
{
    l->current = l->last;
}




int isLast(list* l)
{
return l->current == l->last && l->current != NULL;
}


int empty(list * l)
{
    return (l->first == NULL && l->last == NULL);
}

int oneElement(list * l)
{
    return (l->first != NULL && l->first == l->last);
}

void printList(list * l)
{
    midiList* n;
    printf("{");
    n = l->first;
    while (n != NULL)
    {
        printf(" Midi event : %d  Delay : %f  Midi note : %2x attack : %2x \n ", n->midiEvent, n->delay, n->midiNote,n->attack);

        n = n->next;
    }
    freeNodeList(n);
    printf("}\n");
}
