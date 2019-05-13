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
    list *l = (list*) malloc(sizeof(list));
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


int empty(list * l)
{
    return (l->first == NULL || l->last == NULL);
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
        if (n->attack > 127){
            printf ("JES SUIS TROP FORT");
        }
        n = n->next;
    }
    printf("}\n");
}
