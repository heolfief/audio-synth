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
}



void setAsBeginDataRange(FILE *f){
    unsigned char * buffer = BlockFileReader(f,1);
    passedMetaData(f);
    while(buffer[0]== 0x4d || buffer[0] == 0x54 || buffer[0]== 0x72 || buffer[0]== 0x6b){
        BlockFileReader(f,1);
    }
    free(buffer);

}

void passedMetaData(FILE *f){
    unsigned char * test= BlockFileReader(f,1);
    unsigned char * buffer = NULL;
    __uint16_t nbData;

    while (test[0]== 0xFF){
        buffer= BlockFileReader(f,2);
        nbData = buffer[1];
        fseek(f,nbData,SEEK_CUR);
        test= BlockFileReader(f,1);
    }

    fseek(f,-1,SEEK_CUR);
    free(test);
    free(buffer);
}

u_int16_t  * readDataRangeSorted ( u_int32_t size) {
    u_int16_t  * DataRange = NULL;
    FILE *fichier =openFile(tmp, "r+", RETOUR);
    DataRange = (u_int16_t*) BlockFileReader(fichier,size);
    return DataRange;
}






__uint16_t  *readDataRange (FILE * f){
    unsigned char * buffer = BlockFileReader(f,1);
    u_int16_t * DataRange =NULL;
    u_int32_t size;
    setAsBeginDataRange(f);




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