//
// Created by vincent on 10/02/19.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "midi.h"
#include "../fichier/fichier.h"




void fillHeaderRead (Header * H, FILE * f){
    unsigned char *  buffer = BlockFileReader(f,14);
    for (int i =0; i<4;i++){
        H->MTHD[i]= buffer[i];
    }
    if (H->MTHD[0]!= 0x4d && H->MTHD[1]!= 0x54 && H->MTHD[2]!=0x68 && H->MTHD[3]!=0x64){
        printf("unrecognized file");
        return;
    }
    for (int i= 4; i<8; i++){
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
    while(buffer[0]== 0x4d || buffer[0] == 0x54 || buffer[0]== 0x72 || buffer[0]== 0x6b){
       buffer = BlockFileReader(f,1);

    }
    free(buffer);
    moveFile(f,-1);
}

u_int32_t passedMetaData(FILE *f,u_int32_t size, __uint32_t currentLine) {
    unsigned char *test = BlockFileReader(f, 1);
    unsigned char *buffer = NULL;
    __uint16_t nbData;


    while (test[0] == 0xFF && currentLine <size) {
        buffer = BlockFileReader(f, 2);
       if (buffer[0] == 0x2F && buffer[1] == 0x00){
            return size;
        }
        nbData = buffer[1];
        moveFile(f, nbData);
        test = BlockFileReader(f, 1);
        currentLine ++;
    }

    moveFile(f, -1);

    free(test);
    free(buffer);
    return currentLine;
}

u_int16_t  * readDataRangeSorted ( u_int32_t  size) {
    u_int16_t  * DataRange = NULL;
    FILE *fichier = openFile(TMP, "r+", RETOUR);
    DataRange = (u_int16_t*) BlockFileReader(fichier,size);
    return DataRange;
}

u_int32_t recordDataRange (FILE *f,u_int32_t size){
    FILE * FILERecord  = fopen(TMP,"w+");
    u_int32_t  sizeTMP= 0;
    unsigned char * buffer = NULL;
    __uint32_t currentLine =0;
    currentLine = passedMetaData( f, size,currentLine);
     while(!feof((f)) && currentLine<size){
        buffer = BlockFileReader(f,1);
        fprintf(FILERecord,"%2x  ", buffer[0]);
        free(buffer);
        currentLine = passedMetaData(f, size, currentLine) ;
        sizeTMP ++;
        currentLine++;


    }

   closeFile(FILERecord);
    return sizeTMP;
}


u_int32_t  getSizeDataRange(FILE *f){
    u_int32_t  size;
    unsigned char * buffer =NULL;
   buffer= BlockFileReader(f,4);
   size =  buffer[0]*16777216 + buffer[1]*65536 + buffer[2]*256 +buffer[3];
    return size;


}



__uint16_t  * readDataRange (FILE * f){
    unsigned char * buffer = BlockFileReader(f,1);
    u_int16_t * DataRange =NULL;
    u_int32_t  size;
    setAsBeginDataRange(f);
    size = getSizeDataRange(f);
    size = recordDataRange(f,size);
    DataRange =readDataRangeSorted(size);
    return DataRange;

}



/*
void setAtData(FILE *f){
    unsigned char * buffer = NULL;
    long int offset;
    buffer=BlockFileReader(f,9);
    buffer=BlockFileReader(f,1);
    printf ("%x",buffer[0]);
    while(buffer[0]== 0xFF ){
        buffer=BlockFileReader(f,2);
        offset = buffer[1];
        printf ("%ld",offset);

        fseek(f,,SEEK_CUR);
        buffer=BlockFileReader(f,1);
    }

    buffer=BlockFileReader(f,1);
    printf ("%x",buffer[0]);

}*/