#include "listDataRange.h"
#include "listmidi.h"
#include "stdio.h"
#include "stdlib.h"
#include "../core/note/adsr.h"

midiList * new_Midi_List(midiList *current, midiList *previous)
{

    current->nextmidiList = previous;
    current ->accrued_delay = 0;

    return current;				/*Return of ptr for DataRange List*/
}







dataRangeList *  initdataRangeList()
{

    dataRangeList * l = (dataRangeList*) malloc(sizeof(dataRangeList));
    if (l == NULL)
    {
        sys_print_error("initilisation DataRangelist is NULL");

    }

    l->currentDataRange = NULL;
    l->firstDataRange = NULL;
    l->lastDataRange = NULL;

    return l;
}


void freeDataRange(dataRangeList * l){
    while(!emptyDataRange(l)) deleteFirstDataRange(l);
    free(l);


}



void setOnFirstDataRange(dataRangeList * l){
    l->currentDataRange = l->firstDataRange;
}



int deleteFirstDataRange(dataRangeList *l){
    if (emptyDataRange(l))
        return 0;
    midiList * toDel = (midiList*) l->firstDataRange;
    l->firstDataRange = l->firstDataRange->nextmidiList;
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



int emptyDataRange(dataRangeList * l)
{
    if (l==NULL)
        return 1;
    return (l->firstDataRange == NULL);
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

