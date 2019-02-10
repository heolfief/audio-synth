#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include "fichier.h"



int main(int argc, char *argv[])
{



  FILE * test;

  test= ouvrirFichier("Mario_SMF1.mid","r",RETOUR);
    unsigned char * mot = lireBlockFichier(test,60);


    for (int i =0 ; i<60;i++) {
        printf("%3x", mot[i]);
    }
   fermerFichier(test);

  }

