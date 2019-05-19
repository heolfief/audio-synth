#include "listDataRange.h"
#include "listmidi.h"




midiList * newDataRange(midiList * previous)
{
    midiList * new = initList();  /*Allocation de l'espace mmoire*/
    new ->accrued_delay = 0;
    previous->nextmidiList = new;
    new->nextmidiList = NULL;
    return new;				/*Return du pointeur vers la node cre*/
}







dataRangeList * initdataRangeList()
{
    dataRangeList * l =NULL;

    l = (dataRangeList*) malloc(sizeof(dataRangeList));
    if (l == NULL)
    {
        fprintf(stderr, "Warning/error : allocation memoire dynamique chou dans la fonction %s\n", __FUNCTION__);
        return NULL;		/*L'allocation  chou*/
    }

    l->current = (dataRangeList*) malloc(sizeof(dataRangeList));
    l->first =   l->current;
    l->last = NULL;

    return l ;


}


void freeDataRange(dataRangeList * l){
    while(!empty(l)) deleteFirstDataRange(l);



}



void setOnFirstDataRange(dataRangeList * l){
    l->current = l->first;
}



int deleteFirstDataRange(dataRangeList *l){
    if (empty(l))
        return 0;
    midiList * toDel = l->first;
    l->first = toDel->nextmidiList;
    freeList(toDel);
    if (emptyDataRange(l))
    {
        l->last = NULL;

    }
    setOnFirstDataRange(l);
    return 1;

}



void nextDataRange(dataRangeList * l)
{
    if(OutOfDataRangeList(l))
        return;
    midiList *n ;
    n=l->current;
    l->current = n->nextmidiList;
}

int OutOfDataRangeList(dataRangeList * l)
{
    return l->current == NULL;
}


void setOnLastDataRange(dataRangeList* l)
{
    l->current = l->last;
}


int LastDataRange(dataRangeList * l)
{
    return l->current == l->last && l->current != NULL;
}


int emptyDataRange(dataRangeList * l)
{
    return (l->first == NULL && l->last == NULL);
}



