#include <stdio.h>
#include "listmidi.h"
#include <stdlib.h>




midiList * newNodeList(__uint16_t * midiNote, __uint16_t *attack, __uint16_t  *midiEvent, __uint32_t  delay, midiList * next)
{
    midiList * new = (midiList*)malloc(sizeof(midiList));  /*Allocation de l'espace mmoire*/
    if (new == NULL)
    {
        fprintf(stderr, "Warning/error : allocation mmoire dynamique chou dans la fonction %s\n", __FUNCTION__);
        return NULL;		/*L'allocation  chou*/
    }
    new->midiNote = (*midiNote);
    new->midiEvent= (*midiEvent);
    new->attack= (*attack);
    new->delay = delay;
    next->next = new;
    new->next = NULL;
    return new;				/*Return du pointeur vers la node cre*/
}

/*

void initList(list * l)
{
    l->first  ;
    l->current = NULL;
    l->last = NULL;
}
*/

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
        printf(" %d %2X %2x %2x \n ", n->midiEvent, n->delay, n->midiNote,n->attack);
        n = n->next;
    }
    printf("}\n");
}
