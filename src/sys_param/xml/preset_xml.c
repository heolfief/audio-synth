/**
 * \file preset_xml.c
 * \brief Preset (XML file) functions implementation.
 *
 *
 * Here are implemented the functions to handle preset XML files
 */

#include "preset_xml.h"

// Global system parameters defined in main.c
extern Sys_param* sys_param;

double read_XML_param(xmlChar* param)
{
    if(param == NULL)
    {
        //sys_print_error("Parameter is NULL");
        return -1;
    }
    return atof((const char*)param);
}

int write_XML_param(xmlChar* param, double value)
{
    if(param == NULL)
    {
        //sys_print_error("Parameter is NULL");
        return -1;
    }
    char buff[20];

    sprintf(buff, "%lf", value);
    strcpy((char*)param, buff);

    return 0;
}

int load_preset(const char* filename)
{
    xmlDocPtr doc = NULL;
    char filename_relat[30]= "../presets/";

    if(filename == NULL)
    {
        sys_print_error("Filename is NULL");
        return -1;
    }

    strcat(filename_relat, filename);

    // Parse XML file
    doc = xmlParseFile(filename_relat);
    if(doc == NULL)
    {
        sys_print_error("Cannot parse preset file");
        return -1;
    }

    // Load oscillator 1 parameters
    sys_param->osc1->onoff  = (OnOff)read_XML_param(xmlosc1->xmlonoff);
    sys_param->osc1->amp    = (Uint16)read_XML_param(xmlosc1->xmlamp);
    sys_param->osc1->detune = (Sint8)read_XML_param(xmlosc1->xmldetune);
    sys_param->osc1->duty   = (Uint8)read_XML_param(xmlosc1->xmlduty);
    sys_param->osc1->wave   = (Waveform)read_XML_param(xmlosc1->xmlwave);

    // Load oscillator 2 parameters
    sys_param->osc2->onoff  = (OnOff)read_XML_param(xmlosc2->xmlonoff);
    sys_param->osc2->amp    = (Uint16)read_XML_param(xmlosc2->xmlamp);
    sys_param->osc2->detune = (Sint8)read_XML_param(xmlosc2->xmldetune);
    sys_param->osc2->duty   = (Uint8)read_XML_param(xmlosc2->xmlduty);
    sys_param->osc2->wave   = (Waveform)read_XML_param(xmlosc2->xmlwave);

    // Load oscillator 3 parameters
    sys_param->osc3->onoff  = (OnOff)read_XML_param(xmlosc3->xmlonoff);
    sys_param->osc3->amp    = (Uint16)read_XML_param(xmlosc3->xmlamp);
    sys_param->osc3->detune = (Sint8)read_XML_param(xmlosc3->xmldetune);
    sys_param->osc3->duty   = (Uint8)read_XML_param(xmlosc3->xmlduty);
    sys_param->osc3->wave   = (Waveform)read_XML_param(xmlosc3->xmlwave);

    // Load envelope parameters
    sys_param->env->attack  = read_XML_param(xmlenv->xmlattack);
    sys_param->env->decay   = read_XML_param(xmlenv->xmldecay);
    sys_param->env->sustain = read_XML_param(xmlenv->xmlsustain);
    sys_param->env->release = read_XML_param(xmlenv->xmlrelease);

    // Load other parameters

    // Free xml file
    xmlFreeDoc(doc);

    return 0;
}
