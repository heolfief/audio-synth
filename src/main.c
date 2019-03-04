#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "fichier/fichier.h"
#include "midi/midi.h"


int main(int argc, char *argv[])
{



  FILE * test;

  test= openFile("../fichier_midi/test midi 2 note.mid","r",RETOUR);

    Header h;
    fillHeaderRead(&h,test);
    readDataRange(test);

   closeFile(test);

  }

