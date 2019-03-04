//
// Created by vincent on 10/02/19.
//
#include <stdio.h>
#ifndef MIDI_H
#define MIDI_H
#define TMP "tmp.txt"

typedef struct {
    unsigned char MTHD[4]; // 4 bytes for header flag
    unsigned char SPEC_ADDR[4]; // 4 bytes to inform about the addressing specs
    u_int16_t SMF ; // 2 bytes to indicate the data ranges: 0 only one data range, 1 several tracks played simultaneously, 2 more tracks but to be played one after the other
    u_int16_t MTRK ; // 2 bytes for the number of data ranges
    u_int16_t NOIRE; // 2 bytes: number divisions of the black

} Header;






void fillHeaderRead (Header*H, FILE* f);
__uint16_t  *readDataRange (FILE *f);
__uint16_t  * readDataRangeSorted( u_int32_t size);
void setAsBeginDataRange (FILE *f);
void passedMetaData(FILE *f);
u_int32_t recordDataRange(FILE *f);
u_int32_t getSizeDataRange(FILE *f);

#endif