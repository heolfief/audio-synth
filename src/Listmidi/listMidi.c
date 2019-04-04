#include <stdio.h>
#include "../Listmidi/listMidi.h








midiList * newList(void * ptr, midiList * next);
{
    midiList * new = (midiList*)malloc(sizeof(nodeList));  /*Allocation de l'espace mmoire*/
    if (new == NULL)
    {
        fprintf(stderr, "Warning/error : allocation mmoire dynamique chou dans la fonction %s\n", __FUNCTION__);
        return NULL;		/*L'allocation  chou*/
    }
    new->data = ptr;        /*Initialisation des poiteurs, data vers la donne  stocker, next vers la node suivante et next vers la suivante*/
    new->next = n;


    return new;				/*Return du pointeur vers la node cre*/
}



void initList(list * l)
{
    l->first = NULL;
    l->current = NULL;
    l->last = NULL;
}


int empty(list * l)
{
    return (l->first == NULL || l->last == NULL);
}

int oneElement(list * l)
{
    return (l->first != NULL && l->first == l->last);
}

