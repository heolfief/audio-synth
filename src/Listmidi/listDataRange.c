#include "listDataRange.h"
#include "listmidi.h"
#include "stdio.h"
#include "stdlib.h"



midiList * newDataRange(midiList * current,  midiList * previous)
{

    midiList * new ;

    current->current =current ->first;


    new = current;
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


void nextMidiList(dataRangeList* l)
{
    if(OutOfDataRangeList(l))
        return;
    midiList *n ;
    n=l->currentDataRange;
    l->currentDataRange = n->nextmidiList;
}



dataRangeList *  updateDelayDataRange(dataRangeList * l, int size){
    midiList *m;
    midiData *n;
    l->currentDataRange = l->firstDataRange;
    m=l->currentDataRange;


    for (int i=0;i<size;i++){
        n=m->current;
        if (n!=NULL && m!=NULL)
        {

            m->accrued_delay +=  n->delay;

            l->currentDataRange = m;
        }
         nextDataRange(l);
        m=l->currentDataRange;

    }
    l->currentDataRange = l->firstDataRange;
    m=l->currentDataRange;



    return l;
}



midiData * getFirstNoteToPlay(dataRangeList * l, int size){
double delay =1000000;
static double old_delay;
static int old_dataRange;

int numberOfMidiData = 0;
midiList *m;
midiData *n;
double test = 0;
l->currentDataRange = l->firstDataRange;
m=l->currentDataRange;



for (int i=0; i<size;i++){
    m= l->currentDataRange;
    n = m->current;

    if ( m->current != NULL)
    {

        if (i != old_dataRange && ((m->accrued_delay+n->delay) - old_delay) <= delay )
        {
            numberOfMidiData = i;
            delay = (m->accrued_delay+n->delay) - old_delay;

        }
        else if ((m->accrued_delay + n->delay)<=delay){
            numberOfMidiData = i;
            delay = m->accrued_delay + n->delay;


        }

    }

        nextDataRange(l);



}
l->currentDataRange = l->firstDataRange;
m=l->currentDataRange;


for (int i=0 ; i<(numberOfMidiData);i++){
    nextDataRange(l);
    m= l->currentDataRange;

}
    n = m->current;
if (old_dataRange == numberOfMidiData){
    test=n->delay;
old_delay =0;

}
else
{
    old_dataRange = numberOfMidiData;
   test = n->delay;
    n->delay =  (n->delay - old_delay);
    double temp = n->delay;
    old_delay = m->accrued_delay + temp;
}

    m->accrued_delay +=n->delay;
//printf("%d delay :%d midiNote : %2X, accrued : %f  \n",numberOfMidiData,n->delay, n->midiNote , m->accrued_delay);








next(m);
return n;

}

