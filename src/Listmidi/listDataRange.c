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

    l->currentDataRange = (dataRangeList*) malloc(sizeof(dataRangeList));
    l->firstDataRange =   l->currentDataRange;
    l->lastDataRange = NULL;

    return l ;


}


void freeDataRange(dataRangeList * l){
    while(!empty(l)) deleteFirstDataRange(l);



}



void setOnFirstDataRange(dataRangeList * l){
    l->currentDataRange = l->firstDataRange;
}



int deleteFirstDataRange(dataRangeList *l){
    if (empty(l))
        return 0;
    midiList * toDel = l->firstDataRange;
    l->firstDataRange = toDel->nextmidiList;
    freeList(toDel);
    if (emptyDataRange(l))
    {
        l->lastDataRange = NULL;

    }
    setOnFirstDataRange(l);
    return 1;

}



void nextDataRange(dataRangeList * l)
{
    if(OutOfDataRangeList(l))
        return;
    midiList *n ;
    n=l->currentDataRange;
    l->currentDataRange = n->nextmidiList;
}

int OutOfDataRangeList(dataRangeList * l)
{
    return l->currentDataRange == NULL;
}


void setOnLastDataRange(dataRangeList* l)
{
    l->currentDataRange = l->lastDataRange;
}


int LastDataRange(dataRangeList * l)
{
    return l->currentDataRange == l->lastDataRange && l->currentDataRange != NULL;
}


int emptyDataRange(dataRangeList * l)
{
    return (l->firstDataRange == NULL && l->lastDataRange == NULL);
}




void updateDelayDataRange(dataRangeList * l, int size){
    midiList *m;
    midiData *n;
    m=l->firstDataRange;
    for (int i=0;i<size;i++){
        m=l->currentDataRange;
            n=m->current;
        m->accrued_delay = m->accrued_delay + n->delay;
    m->nextmidiList;
    printf("%d \n",m->accrued_delay);
    }
}


//midiData * getFirstNoteToPlay(dataRangeList * l, int size){




}

