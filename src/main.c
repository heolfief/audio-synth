#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "fichier/fichier.h"
#include "midi/midi.h"


int main(int argc, char *argv[])
{



  FILE * test;

  test= ouvrirFichier("../fichier_midi/test midi une note.mid","r",RETOUR);

    Header h;
    fillHeaderRead(&h,test);

   fermerFichier(test);

  }

