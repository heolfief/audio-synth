
//
// Created by vincent on 10/02/19.
//
#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"




FILE * openFile (char * nom, char * mode, TypeRetour t){
    FILE * fichier;
    if ((fichier = fopen(nom,"r")) == (FILE *) NULL){
        printf("open file error");
        return fichier;
    }
    return fichier;
}

int closeFile(FILE * fichier){
   return( fclose (fichier));

}


unsigned char * BlockFileReader (FILE * fichier, u_int32_t nombre){
    unsigned char * buffer;
    if ((buffer = (unsigned char *) malloc(sizeof(unsigned char)*nombre)) == NULL){
        printf("memory allocation error");
        exit (568);
    }

    fread(buffer,sizeof(unsigned char),nombre,fichier);
    return buffer;


}

int removeFile(FILE *f){
    return (removeFile(f));



}


