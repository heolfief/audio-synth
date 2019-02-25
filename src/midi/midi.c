//
// Created by vincent on 10/02/19.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "midi.h"
#include "../fichier/fichier.h"




void fillHeaderRead (Header * H, FILE * f){
    unsigned char *  buffer = lireBlockFichier(f,14);
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