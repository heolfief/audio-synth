#include <stdio.h>
#include "../Listmidi/listMidi.h








midiList * newList(__uint16_t  midiNote, __uint16_t attack, __uint16_t  midiEvent, __uint32_t  delay, midiList * next);
{
    midiList * new = (midiList*)malloc(sizeof(nodeList));  /*Allocation de l'espace mmoire*/
    if (new == NULL)
    {
        fprintf(stderr, "Warning/error : allocation mmoire dynamique chou dans la fonction %s\n", __FUNCTION__);
        return NULL;		/*L'allocation  chou*/
    }
    new->midiNote= midiNote;
    new->midiEvent= midiEvent;
    new->attack= attack;
    new->delay = delay;
    next->next = new;
    new->next = NULL;
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


int insertFirst(list * l, void* data)
{

    midiList* new = newList(data, l->first, NULL);
    if (new == NULL)
        return 0;
    if (empty(l))
        l->last = l->current = new;
    else
        l->first->previous = new;
    l->first = new;

    return 1;

}
