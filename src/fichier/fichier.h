/**
 * \file fichier.h
 * \brief File functions
 *
 *
 * Here are defined the data structure of the Open File, and the related functions
 */

#include <stdio.h>

#ifndef FICHIER_H
#define FICHIER_H

/**
 * \enum TypeRetour
 * \brief define an kind of return
 *
 * This enum defines the various return : Arret, Retour
 */


typedef enum {ARRET,RETOUR}TypeRetour;

/**
 * \fn FILE * openFile (char * nom, char * mode, TypeRetour t)
 * \brief Function to open a target File
 *
 * \param name Name of the target file
 * \param mode Opening method : r+: reading, w+: writting ...
 * \param t TypeRetour kind of return
 *
 * \return the target File open
 */

FILE * openFile (char * name, char * mode, TypeRetour t);
/**
 * \fn int closeFile(FILE * fichier);
 * \brief Function to close a file
 *
 * \param file Target File
 *
 * \return 0 if everything went OK, -1 otherwise
 */

int closeFile(FILE * file);
/**
 * \fn unsigned char * BlockFileReader (FILE * fichier, u_int32_t  nombre)
 * \brief Function to read various number of bytes in a File
 *
 * \param file Target File
 * \param number Number of bytes you want to read
 *
 * \return allocated buffer with result of reading on a file
 */

unsigned char * BlockFileReader (FILE * file, u_int32_t  number);
/**
 * \fn int removeFile(FILE *f)
 * \brief Function to remove a file
 *
 * \param file Target file
 *
 * \return 0 if everything went OK, -1 otherwise
 */

int removeFile(FILE *file);
/**
 * \fn void moveFile (FILE *f, int number)
 * \brief Function to move the current postion to another position
 *
 * \param file Target file
 * \param number Number of bytes who wants to move
 *
 */

void moveFile (FILE *file, int number);







#endif //AUDIO_SYNTH_FICHIER_H
