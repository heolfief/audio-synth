#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "fichier/fichier.h"
#include "midi/midi.h"


int main(int argc, char *argv[])
{

    u_int32_t * DataRange;

  FILE * test;

  test= openFile("../fichier_midi/clairdelune.mid","r",RETOUR);

    Header h;
    fillHeaderRead(&h,test);
    //playDataRange=readDataRange(test);
    //playDataRange(DataRange);
   closeFile(test);

  }

