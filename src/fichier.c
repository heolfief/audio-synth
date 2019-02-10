
//
// Created by vincent on 10/02/19.
//
#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"



FILE * ouvrirFichier (char * nom, char * mode, TypeRetour t){
    FILE * fichier;
    if ((fichier = fopen(nom,"r")) == (FILE *) NULL){
        printf("open file error");
        exit(567);
    }
    return fichier;
}

void fermerFichier(FILE * fichier){
    fclose (fichier);

}


unsigned char * lireBlockFichier (FILE * fichier, int nombre){
    unsigned char * buffer;
    if ((buffer = (unsigned char *) malloc(sizeof(unsigned char)*nombre)) == NULL){
        printf("memory allocation error");
        exit (568);
    }
    fread(buffer,sizeof(unsigned char),nombre,fichier);
    return buffer;


}