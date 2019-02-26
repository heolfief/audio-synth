//
// Created by vincent on 10/02/19.
//
#include <stdio.h>

#ifndef FICHIER_H
#define FICHIER_H

typedef enum {ARRET,RETOUR}TypeRetour;


FILE * openFile (char * nom, char * mode, TypeRetour t);
int closeFile(FILE * fichier);
unsigned char * BlockFileReader (FILE * fichier, u_int32_t  nombre);
int removeFile(FILE *f);








#endif //AUDIO_SYNTH_FICHIER_H
