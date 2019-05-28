/**
 * \file listDataRange.c
 * \brief BRIEF DESCRIPTION
 *
 *  DESCRIPTION
 */

#include "listDataRange.h"

midiList *new_Midi_List(midiList *current, midiList *previous)
{
    current->nextmidiList = previous;
    current->accrued_delay = 0;

    return current;                /*Return of ptr for DataRange List*/
}

dataRangeList *initdataRangeList()
{
    dataRangeList *l = (dataRangeList *) malloc(sizeof(dataRangeList));
    if (l == NULL)
    {
        sys_print_error("initilisation DataRangelist is NULL");
        return NULL;
    }

    l->currentDataRange = NULL;
    l->firstDataRange = NULL;
    l->lastDataRange = NULL;

    return l;
}

void freeDataRange(dataRangeList *l)
{
    while (!emptyDataRange(l))
    {
        deleteFirstDataRange(l);
    }
}

void setOnFirstDataRange(dataRangeList *l)
{
    l->currentDataRange = l->firstDataRange;
}

int deleteFirstDataRange(dataRangeList *l)
{
    if (emptyDataRange(l))
    {
        return 0;
    }
    midiList *toDel = (midiList *) l->firstDataRange;
    l->firstDataRange = l->firstDataRange->nextmidiList;
    freeList(toDel);
    free(toDel);
    if (emptyDataRange(l))
    {
        l->lastDataRange = NULL;

    }

    setOnFirstDataRange(l);
    return 1;
}

void nextDataRange(dataRangeList *l)
{
    if (OutOfDataRangeList(l))
    {
        return;
    }
    midiList *n;
    n = l->currentDataRange;
    l->currentDataRange = n->nextmidiList;
}

int OutOfDataRangeList(dataRangeList *l)
{
    return l->currentDataRange == NULL;
}

int emptyDataRange(dataRangeList *l)
{
    if (l == NULL)
    {
        return 1;
    }
    return (l->firstDataRange == NULL);
}

int getCount(dataRangeList *l)
{
    int count = 0; // Initialize count
    midiList *current = l->firstDataRange; // Initialize current
    while (current != NULL)
    {
        count++;
        current = current->nextmidiList;
    }
    return count;
}

dataRangeList *updateDelayDataRange(dataRangeList *l)
{
    midiList *m;
    midiData *n;
    l->currentDataRange = l->firstDataRange;
    m = l->currentDataRange;
    static int g = 0;

    for (int i = 0; i < getCount(l); i++)
    {

        if (g == 0)
        {
            m->current = m->first;
        }

        if (l->currentDataRange != NULL)
        {
            n = m->current;
            if (n != NULL)
            {
                m->accrued_delay += n->delay;
                l->currentDataRange = m;
            }
        }
        nextDataRange(l);
        m = l->currentDataRange;

    }
    l->currentDataRange = l->firstDataRange;

    g++;

    return l;
}

midiData *getFirstNoteToPlay(dataRangeList *l)
{
    double delay = 1000000;
    static double old_delay;
    static int old_dataRange;
    static int g = 0;
    int numberOfMidiData = 0;
    midiList *m;
    midiData *n;
    l->currentDataRange = l->firstDataRange;

    for (int i = 0; i < getCount(l); i++)
    {
        m = l->currentDataRange;
        if (g == 0)
        {
            setOnFirst(m);
        }

        n = m->current;

        if (m->current != NULL && n->next != NULL)
        {

            if (delay >= m->accrued_delay)
            {
                delay = m->accrued_delay;
                numberOfMidiData = i;
            }

        }
        nextDataRange(l);
    }

    g++;

    l->currentDataRange = l->firstDataRange;
    m = l->currentDataRange;

    for (int i = 0; i < (numberOfMidiData); i++)
    {
        nextDataRange(l);
        m = l->currentDataRange;

    }
    double temp;
    n = m->current;
    if (old_dataRange == numberOfMidiData)
    {
        old_delay = 0;
        temp = n->delay;

    }
    else
    {
        old_dataRange = numberOfMidiData;
        temp = n->delay;
        old_delay = temp;
    }

    m->accrued_delay += n->delay;

    next(m);

    setOnFirstDataRange(l);
    m = l->firstDataRange;
    for (int i = 0; i < getCount(l); i++)
    {
        if (numberOfMidiData != i)
        {
            m->accrued_delay = m->accrued_delay - temp;
        }
        nextDataRange(l);

        m = l->currentDataRange;
    }

    n->delay = n->delay - old_delay;

    return n;
}

