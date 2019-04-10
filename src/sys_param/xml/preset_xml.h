/**
 * \file preset_xml.h
 * \brief Preset (XML file) functions definition.
 *
 *
 * Here are defined the functions to handle preset XML files
 */

#ifndef AUDIO_SYNTH_PRESET_XML_H
#define AUDIO_SYNTH_PRESET_XML_H

#include <SDL2/SDL_stdinc.h>
#include <libxml/parser.h>
#include <string.h>
#include "../sys_param.h"
#include "../../system/error_handler.h"
#include "../../core/audio_core.h"

#define xmlvalue    children->content

// In XML file, each tab is considered as a child. Therefore there is a "next->" statement in between each pair of "next" statements.
#define xmlosc1     children->children->next
#define xmlosc2     xmlosc1->next->next
#define xmlosc3     xmlosc2->next->next

// Relative to xmloscX
#define xmlonoff    children->next->xmlvalue
#define xmlamp      children->next->next->next->xmlvalue
#define xmldetune   children->next->next->next->next->next->xmlvalue
#define xmlduty     children->next->next->next->next->next->next->next->xmlvalue
#define xmlwave     children->next->next->next->next->next->next->next->next->next->xmlvalue

#define xmlenv      xmlosc3->next->next

// Relative to xmlenv
#define xmlattack   children->next->xmlvalue
#define xmldecay    children->next->next->next->xmlvalue
#define xmlsustain  children->next->next->next->next->next->xmlvalue
#define xmlrelease  children->next->next->next->next->next->next->next->xmlvalue

#define xmlfilt      xmlenv->next->next

// Relative to xmfilt
#define xmlfiltertype children->next->xmlvalue
#define xmlcutofffreq children->next->next->next->xmlvalue
#define xmlresonance  children->next->next->next->next->next->xmlvalue

/**
 * \fn double read_XML_param(xmlChar* param)
 * \brief Reads parameter from XML preset file
 *
 * \param param the address of the xmlChar parameter to read
 *
 * \return the read parameter
 */
double read_XML_param(xmlChar *param);

/**
 * \fn int write_XML_param(xmlChar* param, double value)
 * \brief Writes parameter to XML preset file
 *
 * \param param the address of the xmlChar parameter to change
 * \param value the value to write
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int write_XML_param(xmlChar *param, double value);

/**
 * \fn int load_preset(const char* filename)
 * \brief Load system parameters from an XML preset file
 *
 * \param filename the name of the preset file (relative to project's root folder)
 * \param sys_param the system parameters
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int load_preset(const char *filename, Sys_param *sysParam);

/**
 * \fn int save_preset(const char* filename)
 * \brief Save system parameters to an XML preset file
 *
 * \param filename the name of the preset file (relative to project's root folder)
 * \param sys_param the system parameters
 *
 * \return 0 if everything went OK, -1 otherwise
 */
int save_preset(const char *filename, Sys_param *sysParam);

#endif //AUDIO_SYNTH_PRESET_XML_H
