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




void fillHeaderRead (Header * H, FILE * f){
    unsigned char *  buffer = BlockFileReader(f,14);//control that the file is a midi file, with the Header flag MTHD
    for (int i =0; i<4;i++){
        H->MTHD[i] = buffer[i];
        if (H->MTHD[0]!= 0x4d && H->MTHD[1]!=0x54 && H->MTHD[2] != 0x68 && H->MTHD[3] != 0x64 ) // header number of a midi file
            printf("unrecognized file");
    }

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
    moveFile(f,-1);
}

/*
int skipMetaData(int i, __uint16_t ) {
    unsigned char *test = BlockFileReader(f, 1); // buffer for know if they have a 0xff
    unsigned char *buffer = NULL;
    __uint16_t nbData;

    while (test[0] == 0xFF && currentLine <size) {
        buffer = BlockFileReader(f, 2); // buffer of two for know size of meta data
       if (buffer[0] == 0x2F && buffer[1] == 0x00){ // flags of end of the data Range
            return size;
        }
        nbData = buffer[1];
        moveFile(f, nbData); // move the position in a file
        test = BlockFileReader(f, 1);
        currentLine ++; // Position updated +1
    }
    moveFile(f, -1); // Position updated -1 because of the first read of this function
    free(test);
    free(buffer);
    return currentLine;
}
*/

u_int16_t  * readDataRange (u_int32_t  sizeDataRange,FILE *fichier) {
    u_int16_t * DataRange;
    DataRange = (u_int16_t*) BlockFileReader(fichier,sizeDataRange);
    return DataRange;
}


void playDataRange (u_int16_t * DataRange,Header * H){
    u_int16_t dataDelay [4];
    u_int16_t delay;
    u_int16_t * midiNote = NULL;
    u_int16_t * attack = NULL;
    enum event * midiEvent =NULL;
    int power = 0;
    int i = 0;


while (DataRange[i]!=0xFF && DataRange [i+1] != 0x2F && DataRange[i+2] != 0x00){
    if (DataRange[i]>127){
        dataDelay [power] = DataRange[i];
        power += 1;

    }
    else {
       delay = calculDelay(dataDelay, power, H->NOIRE );
        i += readEvent(midiNote,attack,midiEvent,DataRange,i);
        // fill list (delay)


        power = 0;


        //init dataDelay
    }






i +=1;

}

}


u_int32_t calculDelay(u_int16_t * DataDelay,int power, u_int16_t Noire){
    int res = 0;
    int length = power;
    for(int i = 0;i<length;i++){

        res += DataDelay[i]*pow(126,(double) power);
        power --;

    }
    res = res /Noire;
    return res;
}

int  readEvent (__uint16_t * midiNote, u_int16_t * attack, enum event * midiEvent,u_int16_t * DataRange , int i){

    int res = 0;
    i +=1;
    switch (DataRange[i]) {
        case 0xFF:
            if (DataRange [i+1]== 0x2f && DataRange[i+2]== 0x00) // just to be sure
                break;
          //  i+= skipMetaData()




            break;
        case 0x9 :
            // note on
            break;
        case 0x8 :
            // note off
            break;
       /* case 0xA || 0XB || 0XE:
            i += 3;
            break;
        case 0xC || 0xD:
            i += 2;
            break;
     */   default :
            printf("error file courrupted");
            break;
    }
    return i;
}








/*
u_int32_t writeRomDataRange (FILE *f,u_int32_t size){
    FILE * FILERecord  = fopen(TMP,"w+");
    u_int32_t  sizeTMP= 0;
    unsigned char * buffer = NULL;
    __uint32_t currentLine =0;
    currentLine = skipMetaData( f, size,currentLine);
     while(!feof((f)) && currentLine<size){
        buffer = BlockFileReader(f,1);
        fprintf(FILERecord,"%2x  ", buffer[0]);
        free(buffer);
        currentLine = skipMetaData(f, size, currentLine) ;
        sizeTMP ++;
        currentLine++;


    }

   closeFile(FILERecord);
    return sizeTMP;
}
*/

u_int32_t  getSizeDataRange(FILE *f){
    u_int32_t  size;
    unsigned char * buffer =NULL;
   buffer= BlockFileReader(f,4);
   size =  buffer[0]*16777216 + buffer[1]*65536 + buffer[2]*256 +buffer[3];
    return size;
}











/*
void playDataRange (u_int32_t DataRangeSorted){









}

*/




