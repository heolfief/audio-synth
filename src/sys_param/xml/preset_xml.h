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
#define xmlosconoff    children->next->xmlvalue
#define xmloscamp      children->next->next->next->xmlvalue
#define xmloscdetune   children->next->next->next->next->next->xmlvalue
#define xmloscduty     children->next->next->next->next->next->next->next->xmlvalue
#define xmloscwave     children->next->next->next->next->next->next->next->next->next->xmlvalue

#define xmlenv      xmlosc3->next->next

// Relative to xmlenv
#define xmlenvattack   children->next->xmlvalue
#define xmlenvdecay    children->next->next->next->xmlvalue
#define xmlenvsustain  children->next->next->next->next->next->xmlvalue
#define xmlenvrelease  children->next->next->next->next->next->next->next->xmlvalue



#define xmlflanger  xmlenv->next->next

// Relative to xmlflanger
#define xmlflangonoff  children->next->xmlvalue
#define xmlflanglfowave  children->next->next->next->xmlvalue
#define xmlflanglfofreq  children->next->next->next->next->next->xmlvalue
#define xmlflanglforange children->next->next->next->next->next->next->next->xmlvalue
#define xmlflangdelay    children->next->next->next->next->next->next->next->next->next->xmlvalue
#define xmlflangdepth    children->next->next->next->next->next->next->next->next->next->next->next->xmlvalue



#define xmlampmod   xmlflanger->next->next

// Relative to xmlampmod
#define xmlmodonoff  children->next->xmlvalue
#define xmlmodlevel  children->next->next->next->xmlvalue
#define xmlmodfreq   children->next->next->next->next->next->xmlvalue
#define xmlmodwave   children->next->next->next->next->next->next->next->xmlvalue
#define xmlmodduty   children->next->next->next->next->next->next->next->next->next->xmlvalue



#define xmldist      xmlampmod->next->next

// Relative to xmdist
#define xmldistonoff  children->next->xmlvalue
#define xmldistlevel  children->next->next->next->xmlvalue
#define xmldistwet    children->next->next->next->next->next->xmlvalue



#define xmllfofilt    xmldist->next->next

// Relative to xmflfoilt
#define xmllfofiltonoff        children->next->xmlvalue
#define xmllfofiltfilttype        children->next->next->next->xmlvalue
#define xmllfofiltfiltfreq        children->next->next->next->next->next->xmlvalue
#define xmllfofiltlfofreq         children->next->next->next->next->next->next->next->xmlvalue
#define xmllfofiltresonance       children->next->next->next->next->next->next->next->next->next->xmlvalue
#define xmllfofiltwave            children->next->next->next->next->next->next->next->next->next->next->next->xmlvalue
#define xmllfofiltduty            children->next->next->next->next->next->next->next->next->next->next->next->next->next->xmlvalue
#define xmllfofiltfilterexcurs    children->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->xmlvalue



#define xmlfilt      xmllfofilt->next->next

// Relative to xmfilt
#define xmlfiltonoff children->next->xmlvalue
#define xmlfiltfiltertype children->next->next->next->xmlvalue
#define xmlfiltcutofffreq children->next->next->next->next->next->xmlvalue
#define xmlfiltresonance  children->next->next->next->next->next->next->next->xmlvalue



#define xmldelay      xmlfilt->next->next

// Relative to xmldelay
#define xmldelayonoff children->next->xmlvalue
#define xmldelaydelay children->next->next->next->xmlvalue
#define xmldelayfeedback children->next->next->next->next->next->xmlvalue

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
