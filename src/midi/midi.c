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
#include "midi.h"
#include "../fichier/fichier.h"
#include "../Listmidi/listmidi.h"



void fillHeaderRead (Header * H, FILE * f){
    u_int8_t *  buffer = BlockFileReader(f,14);//control that the file is a midi file, with the Header flag MTHD
    for (int i=0; i<4;i++){
        H->MTHD[i] = buffer[i];


    }
    if (H->MTHD[0]!= 0x4d && H->MTHD[1]!=0x54 && H->MTHD[2] != 0x68 && H->MTHD[3] != 0x64 ) // header number of a midi file
        printf("unrecognized file \n");

    for (int i= 4; i<8; i++){   // fill header
        H->SPEC_ADDR[i-4]=buffer[i];
   }
        H->SMF=buffer[8]*256+buffer[9];

        H->MTRK=buffer[10]*256+buffer[11];

        H->NOIRE=buffer[12]*256 + buffer[13];
    free(buffer);
    fseek(f,-1,SEEK_CUR);
}



void setAsBeginDataRange(FILE *f){
    unsigned char * buffer = BlockFileReader(f,1);
    while(buffer[0]== 0x4d || buffer[0] == 0x54 || buffer[0]== 0x72 || buffer[0]== 0x6b){ // go to the begining of data range detect with the flags 0x4d 0x54 0x72 0x6b
       buffer = BlockFileReader(f,1);
    }
    free(buffer);
}





u_int8_t  * readDataRange (u_int32_t  sizeDataRange,FILE *fichier) {
    u_int8_t * DataRange;
    moveFile(fichier,4);
    DataRange = (u_int8_t*) BlockFileReader(fichier,sizeDataRange);
    return DataRange;
}


list * playDataRange (u_int8_t * DataRange,Header * H){
    u_int8_t dataDelay [4];
    double  delay =0;
    u_int8_t  midiNote = 0 ;
    u_int8_t  attack  =0 ;
    enum event  midiEvent;
    int power = 0;
    int i = 0;
    int g=0;
    int newNote= 0;
    list * l = initList();



while (DataRange[i]!=0xFF && DataRange [i+1] != 0x2F && DataRange[i+2] != 0x00){
    if (DataRange[i]>127){
        dataDelay [power] = DataRange[i];
        power += 1;
    }
    else {
        dataDelay [power] = DataRange[i];
        g++;

        delay = calculDelay(dataDelay, power, H->NOIRE );

       newNote = readEvent(&midiNote,&attack,midiEvent,DataRange,&i);

         if (newNote) {

             l->current = newNodeList(midiNote, attack, midiEvent, delay, l->current);
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
return l;
}


double calculDelay(u_int8_t * DataDelay,int power, u_int16_t Noire){
    double res = 0;

    for(int i = 0;i<=power;i++){
        if (power > 0 && i==0  )
       DataDelay[i] =  DataDelay[i] & 0x7F;

        res += DataDelay[i]*pow(126,(double) (power-i));
    }
    res = res / Noire;
    return res;
}

int  readEvent (__uint8_t * midiNote, u_int8_t * attack,  event  midiEvent,u_int8_t * DataRange , int * i ){
    static int g=0; // for running status
    int newNote;
    *i +=1;

    switch (DataRange[*i] & MSKHEX) {
        case 0xF0:
            if (DataRange [*i+1]== 0x2f && DataRange[*i+2]== 0x00) // just to be sure
                break;
           *i+= DataRange[*i+2]+2;
            newNote = 0;
            break;
        case 0x90 :

            midiEvent = ON;

            *midiNote =  DataRange[*i+1];
            *attack = DataRange[*i+2];

            if (DataRange[*i+2] == 0 )
                midiEvent = OFF;
           * i+=2;
            g=1;
            newNote = 1;
            break;
        case 0x80 :
            midiEvent = OFF;
            *midiNote =  DataRange[*i+1];
            *attack =  DataRange[*i+2];
            *i+=2;
            g=0;
            newNote = 1;
            break;
        case  0XE0:
           * i += 3;
            newNote = 0;
            break;
        case  0XB0 :
            *i += 3;
            newNote = 0;
            break;
        case 0xA0 :
           * i += 3;
            newNote = 0;
            break;
        case 0xC0 :
           * i += 2;
            newNote = 0;
            break;
        case 0xD0 :
            *i += 2;
            newNote = 0;
            break;
       default :
           if (g){
               midiEvent = ON;
           }
           *attack =   DataRange[*i+1];
            *midiNote =  DataRange[*i];
            if (DataRange[*i+1] == 0 )
                midiEvent = OFF;

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
    return size;

}






