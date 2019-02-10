//
// Created by vincent on 10/02/19.
//
#include <stdio.h>

#ifndef FICHIER_H
#define FICHIER_H

typedef enum {ARRET,RETOUR}TypeRetour;

FILE * ouvrirFichier (char * nom, char * mode, TypeRetour t);
void fermerFichier(FILE * fichier);
unsigned char * lireBlockFichier (FILE * fichier, int nombre);






#endif //AUDIO_SYNTH_FICHIER_H
