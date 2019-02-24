//
// Created by vincent on 10/02/19.
//
#include <stdio.h>
#ifndef MIDI_H
#define MIDI_H

typedef struct {
    unsigned char MTHD[4]; // 4 bytes for header flag
    unsigned char SPEC_ADDR[4]; // 4 bytes to inform about the addressing specs
    unsigned char SMF [2]; // 2 bytes to indicate the data ranges: 0 only one data range, 1 several tracks played simultaneously, 2 more tracks but to be played one after the other
    unsigned char MTRK [2]; // 2 bytes for the number of data ranges
    unsigned char NOIRE[2]; // 2 bytes: number divisions of the black

} Header;


void fillHeaderRead (Header*H, FILE* f);




#endif