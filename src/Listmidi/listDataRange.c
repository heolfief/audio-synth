#include "listDataRange.h"
#include "listmidi.h"
#include "stdio.h"
#include "stdlib.h"
#include "../core/note/adsr.h"

midiList * newMidiList(midiList *current, midiList *previous)
{

    midiList * new = (midiList *) malloc(sizeof(midiList));
    if (new == NULL)
    {
        sys_print_error("newMidiList is NULL");
    }

    new->nextmidiList =  (midiList*) previous;

    fill_midiList(current,new);
    return new;				/*Return du pointeur vers la node cre*/
}



void fill_midiList(midiList * currentDataRange, midiList * new){

    new = currentDataRange;
    new ->accrued_delay = 0;

}



dataRangeList *  initdataRangeList()
{

    dataRangeList * l = (dataRangeList*) malloc(sizeof(dataRangeList));
    if (l == NULL)
    {
        sys_print_error("initilisation DataRangelist is NULL");

    }

    l->currentDataRange = NULL;
    l->firstDataRange =  NULL;
    l->lastDataRange = NULL;

    return l;
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

        if (l->currentDataRange != NULL)
        {
            n=m->current;
            if (n!=NULL)
            {
                m->accrued_delay += n->delay;
                l->currentDataRange = m;
            }
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



for (int i=0; i<size;i++)
{
    m = l->currentDataRange;


        n = m->current;

        if (m->current != NULL)
        {

            if (i != old_dataRange && ((m->accrued_delay + n->delay) - old_delay) <= delay)
            {
                numberOfMidiData = i;
                delay = (m->accrued_delay + n->delay) - old_delay;

            }
            else if ((m->accrued_delay + n->delay) <= delay)
            {
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
if (old_dataRange == numberOfMidiData ){
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




// si j'ai un null en n ça va me poser des problèmes



next(m);
return n;

}

