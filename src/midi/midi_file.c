/**
 * \file midi.c
 * \brief Midi functions
 *
 *
 * Here are defined the function that works on midi
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "midi_file.h"
#include "../fichier/fichier.h"
#include "../Listmidi/listmidi.h"
#include "../Listmidi/listDataRange.h"
#include "../core/audio_core.h"
#include "../midi/midi_keyboard.h"


void fillHeaderRead (Header * H, FILE * f){
    u_int8_t *  buffer = BlockFileReader(f,14);//control that the file is a midi_test file, with the Header flag MTHD
    for (int i=0; i<4;i++){
        H->MTHD[i] = buffer[i];

    }
    if (H->MTHD[0]!= 0x4d && H->MTHD[1]!=0x54 && H->MTHD[2] != 0x68 && H->MTHD[3] != 0x64 ) // header number of a midi_test file
        printf("unrecognized file \n");

    for (int i= 4; i<8; i++){   // fill header
        H->SPEC_ADDR[i-4]=buffer[i];
   }
        H->SMF=buffer[8]*256+buffer[9];

        H->MTRK=buffer[10]*256+buffer[11];

        H->NOIRE=buffer[12]*256 + buffer[13];


    free(buffer);

}



void setAsBeginDataRange(FILE *f){
    unsigned char * buffer = NULL;
    buffer = BlockFileReader(f,1);

    while(buffer[0]== 0x4d || buffer[0] == 0x54 || buffer[0]== 0x72 || buffer[0]== 0x6b){ // go to the begining of data range detect with the flags 0x4d 0x54 0x72 0x6b
        free(buffer);
       buffer = BlockFileReader(f,1);

    }
    free(buffer);
    fseek(f,-1,SEEK_CUR);
}





u_int8_t  * readDataRange (u_int32_t sizeDataRange,FILE *fichier) {
    u_int8_t * DataRange;

    DataRange = (u_int8_t*) BlockFileReader(fichier,sizeDataRange);
    return DataRange;
}
/*
int * playDataRange (FILE * file){
    Header * H;
    fillHeaderRead(H,file);
    u_int8_t  * MidiData;
    u_int32_t   sizeDataRange;
     initList(l);
    int * DataRange  = malloc(sizeof(MidiData)*H->MTRK);

    for (int i = 0; i<H->MTRK;i++){
        moveFile(file,sizeDataRange);
        setAsBeginDataRange(file);
        MidiData = readDataRange(sizeDataRange,file);
        sortDataRange(MidiData,H,sizeDataRange,l);

    }




    return 1;







}*/












void sortDataRange (__uint8_t * DataRange,Header * H, __uint32_t sizeDataRange,midiList * l){
    u_int8_t dataDelay [4];
    double  delay =0;
    u_int8_t  midiNote = 0 ;
    u_int8_t  attack  =0 ;
    int  midiEvent = 0;
    int power = 0;
    int i = 0;
   static int g=0;
    int newNote= 0;
    int stop = sizeDataRange - 3 ;

while (i<stop ){

    if (DataRange[i]>127){
        dataDelay [power] = DataRange[i];
        power += 1;
    }
    else {
        dataDelay [power] = DataRange[i];


        delay = calculDelay(dataDelay, power, H->NOIRE );


       newNote = readEvent(&midiNote,&attack,&midiEvent,DataRange,&i);



         if (newNote) {


             l->current = new_note_list(midiNote, attack, midiEvent, delay, l->current);
             g++;
             if (g == 1)
                 l->first = l->current;

         }
        power = 0;
        for (int v = 0 ; v<4; v++){
            dataDelay[v] = 0;
        }


    }

i +=1;

}
if (l->current ==NULL && l->first == NULL)
{
    l->current = new_note_list(0, 0, 0, 0, l->current);
    l->first = l->current;
}

g=0;

}


double calculDelay(__uint8_t * DataDelay,int power, __uint16_t Noire){
    double res = 0;

    for(int i = 0;i<=power;i++){
        if (power > 0 && i==0  )
       DataDelay[i] =  DataDelay[i] & 0x7F;

        res += DataDelay[i]*pow(126,(double) (power-i));
    }
    if (power > 1 )
    res = res /Noire;
   // printf("Noire : %d",Noire);

    return res ;
}

int  readEvent (__uint8_t * midiNote, u_int8_t * attack,  int * midiEvent,u_int8_t * DataRange , int * i ){
    static int g=0; // for running status
    int newNote;
    *i +=1;


    switch (DataRange[*i] & MSKHEX) {
        case 0xF0:
           *i+= DataRange[*i+2]+2;
            newNote = 0;
            break;
        case 0x90 :

            *midiEvent = 1;

            *midiNote =  DataRange[*i+1];
            if (DataRange[*i+2] > 127){
                DataRange[*i+2]=127;

            }
            *attack = DataRange[*i+2];


            if (DataRange[*i+2] == 0 )
                *midiEvent = 0;
           * i+=2;
            g=1;
            newNote = 1;
            break;
        case 0x80 :
            *midiEvent = 0;
            *midiNote =  DataRange[*i+1];
            if (DataRange[*i+2] > 127){
                DataRange[*i+2]=127;

            }
            *attack =  DataRange[*i+2];
            *i+=2;
            g=0;
            newNote = 1;
            break;
        case  0XE0:
           * i += 2;
            newNote = 0;
            break;
        case  0XB0 :
            *i += 2;
            newNote = 0;
            break;
        case 0xA0 :
           * i += 2;
            newNote = 0;
            break;
        case 0xC0 :
           * i += 1;
            newNote = 0;
            break;
        case 0xD0 :
            *i += 1;
            newNote = 0;
            break;
       default :
           if (g){
               *midiEvent = 1;
           }
           else{
               *midiEvent = 0;
           }
            if (DataRange[*i+1] > 127){
                DataRange[*i+1]=127;

            }
           *attack =   DataRange[*i+1];
            *midiNote =  DataRange[*i];
            if (DataRange[*i+1] == 0 )
                *midiEvent = 0;

            *i+=1;
            newNote = 1;
            break;
    }
    return newNote ;
}




u_int32_t  getSizeDataRange(FILE *f){
    u_int32_t  size;
    unsigned char * buffer =NULL;
   buffer= BlockFileReader(f,4);
   size = buffer[0]*16777216 + buffer[1]*65536 + buffer[2]*256 +buffer[3];
    free(buffer);
    return size;


}


playMidiFile(Core * audio_core, double currentTime,dataRangeList * l,int size)
{
static controlNote;

static lastTime = 0;
static midiData *n;


if (n == NULL){
l = updateDelayDataRange(l);

n = getFirstNoteToPlay(l);
}




if (currentTime > lastTime + n->delay )  // If time has passed
{
lastTime = currentTime;

if (n->midiEvent == 1)
{
midi_note_ON(audio_core, n->midiNote, n->attack);


}
else if (n->midiEvent == 0)
{
midi_note_OFF(audio_core, n->midiNote);
}

l = updateDelayDataRange(l);

n = getFirstNoteToPlay(l);
}
}




dataRangeList * record_midi_file(char * name)
{
    FILE *test = openFile(name, "r+", RETOUR);
    Header *H = (Header *) malloc(sizeof(Header));
    fillHeaderRead(H, test);
    int size = 0;

    midiData *MidiData;
    midiList *clairdelune = NULL;
    dataRangeList * blue;
    blue = initdataRangeList();

    for (int i = 0; i < H->MTRK - 1; i++)
    {

        clairdelune = initList();
        setAsBeginDataRange(test);
        size = getSizeDataRange(test);
        if (H->SMF == 1 && i == 0)
        {
            moveFile(test, size);
            setAsBeginDataRange(test);
            size = getSizeDataRange(test);
        }

        MidiData = readDataRange(size, test);

        sortDataRange(MidiData, H, size, clairdelune);

        blue->currentDataRange = new_Midi_List(clairdelune, (midiList *) blue->currentDataRange);

        int g = 0;

    }
    closeFile(test);
    return blue;
}





