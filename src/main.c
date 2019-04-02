#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "fichier/fichier.h"
#include "midi/midi.h"


int main(int argc, char *argv[])
{
    u_int16_t MSK = 0xF0;

    u_int32_t * DataRange;
    u_int16_t nombre1 = 0x83;
    unsigned char nombre2 = 0x89;
  FILE * test;

  test= openFile("../fichier_midi/clairdelune.mid","r",RETOUR);

    switch(nombre1 & MSK)
    {
        case 0x80:
            printf ("c'est le 8");
            break;
        case 0x90:
            printf("c'est le 9");
            break;
        default :
            printf ("dommage , %x", nombre1 & MSK);
            break;
    }


  }

