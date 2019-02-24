//
// Created by vincent on 10/02/19.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "midi.h"
#include "../fichier/fichier.h"




void fillHeaderRead (Header * H, FILE * f){
    unsigned char *  buffer = lireBlockFichier(f,16);

    for (int i =0; i<4;i++){
        H->MTHD[i]= buffer[i];
    }

    for (int i= 4; i<8; i++){
        H->SPEC_ADDR[i-4]=buffer[i];
   }
    for (int i=8; i<10; i++){
        H->SMF[i-8]=buffer[i];

    }
    for (int i= 10; i<12; i++){
        H->MTRK[i-10]=buffer[i];

    }
    for (int i= 12; i<14; i++){
        H->NOIRE[i-12]=buffer[i];
       ;
    }
    free(buffer);

}