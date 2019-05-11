#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "fichier/fichier.h"
#include "midi/midi.h"
#include "Listmidi/listmidi.h"



int main(int argc, char *argv[])
{

  FILE * test;
    int size;
    u_int8_t * datarange = NULL;

  test= openFile("../fichier_midi/clairdelune.mid","r",RETOUR);
  Header * H ;
  fillHeaderRead(H,test);
  setAsBeginDataRange(test);
 size =  getSizeDataRange(test);
 datarange = readDataRange(size,test);
 list * l  = playDataRange(datarange,H);
 printList(l);



  }

