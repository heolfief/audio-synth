/**
 * \file preset_xml.c
 * \brief Preset (XML file) functions implementation.
 *
 *
 * Here are implemented the functions to handle preset XML files
 */

#include "preset_xml.h"

double read_XML_param(xmlChar *param)
{
    if (param == NULL)
    {
        //sys_print_error("Parameter is NULL");
        return -1;
    }
    return atof((const char *) param);
}

int write_XML_param(xmlChar *param, double value)
{
    if (param == NULL)
    {
        //sys_print_error("Parameter is NULL");
        return -1;
    }
    char buff[20];

    sprintf(buff, "%g", value);
    strcpy((char *) param, buff);

    return 0;
}

int load_preset(const char *filename, Sys_param *sys_param)
{
    xmlDocPtr doc = NULL;
    char filename_relat[30] = "../presets/";

    if (filename == NULL)
    {
        sys_print_error("Filename is NULL");
        return -1;
    }

    strcat(filename_relat, filename);

    // Parse XML file
    doc = xmlParseFile(filename_relat);
    if (doc == NULL)
    {
        sys_print_error("Cannot parse preset file");
        return -1;
    }

    // Load oscillator 1 parameters
    sys_param->osc1->onoff = (OnOff) read_XML_param(doc->xmlosc1->xmlonoff);
    sys_param->osc1->amp = (Uint16) read_XML_param(doc->xmlosc1->xmlamp);
    sys_param->osc1->detune = (Sint8) read_XML_param(doc->xmlosc1->xmldetune);
    sys_param->osc1->duty = (Uint8) read_XML_param(doc->xmlosc1->xmlduty);
    sys_param->osc1->wave = (Waveform) read_XML_param(doc->xmlosc1->xmlwave);

    // Load oscillator 2 parameters
    sys_param->osc2->onoff = (OnOff) read_XML_param(doc->xmlosc2->xmlonoff);
    sys_param->osc2->amp = (Uint16) read_XML_param(doc->xmlosc2->xmlamp);
    sys_param->osc2->detune = (Sint8) read_XML_param(doc->xmlosc2->xmldetune);
    sys_param->osc2->duty = (Uint8) read_XML_param(doc->xmlosc2->xmlduty);
    sys_param->osc2->wave = (Waveform) read_XML_param(doc->xmlosc2->xmlwave);

    // Load oscillator 3 parameters
    sys_param->osc3->onoff = (OnOff) read_XML_param(doc->xmlosc3->xmlonoff);
    sys_param->osc3->amp = (Uint16) read_XML_param(doc->xmlosc3->xmlamp);
    sys_param->osc3->detune = (Sint8) read_XML_param(doc->xmlosc3->xmldetune);
    sys_param->osc3->duty = (Uint8) read_XML_param(doc->xmlosc3->xmlduty);
    sys_param->osc3->wave = (Waveform) read_XML_param(doc->xmlosc3->xmlwave);

    // Load envelope parameters
    sys_param->env->attack = read_XML_param(doc->xmlenv->xmlattack);
    sys_param->env->decay = read_XML_param(doc->xmlenv->xmldecay);
    sys_param->env->sustain = read_XML_param(doc->xmlenv->xmlsustain);
    sys_param->env->release = read_XML_param(doc->xmlenv->xmlrelease);

    // Load other parameters

    // Free xml file
    xmlFreeDoc(doc);

    return 0;
}

static char *double_to_char(double value)
{
    static char buff[20];
    sprintf(buff, "%g", value);
    return buff;
}

int save_preset(const char *filename, Sys_param *sys_param)
{
    char filename_relat[30] = "../presets/";
    xmlDocPtr doc;
    xmlNodePtr root_node, node_osc1, node_osc2, node_osc3, node_env;

    if (filename == NULL)
    {
        sys_print_error("Filename is NULL");
        return -1;
    }

    strcat(filename_relat, filename);

    doc = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST "parameters");
    xmlDocSetRootElement(doc, root_node);

    node_osc1 = xmlNewChild(root_node, NULL, BAD_CAST "osc1", NULL);
    xmlNewChild(node_osc1, NULL, BAD_CAST "onoff", (xmlChar *) double_to_char(sys_param->osc1->onoff));
    xmlNewChild(node_osc1, NULL, BAD_CAST "amp", (xmlChar *) double_to_char(sys_param->osc1->amp));
    xmlNewChild(node_osc1, NULL, BAD_CAST "detune", (xmlChar *) double_to_char(sys_param->osc1->detune));
    xmlNewChild(node_osc1, NULL, BAD_CAST "duty", (xmlChar *) double_to_char(sys_param->osc1->duty));
    xmlNewChild(node_osc1, NULL, BAD_CAST "wave", (xmlChar *) double_to_char(sys_param->osc1->wave));

    node_osc2 = xmlNewChild(root_node, NULL, BAD_CAST "osc2", NULL);
    xmlNewChild(node_osc2, NULL, BAD_CAST "onoff", (xmlChar *) double_to_char(sys_param->osc2->onoff));
    xmlNewChild(node_osc2, NULL, BAD_CAST "amp", (xmlChar *) double_to_char(sys_param->osc2->amp));
    xmlNewChild(node_osc2, NULL, BAD_CAST "detune", (xmlChar *) double_to_char(sys_param->osc2->detune));
    xmlNewChild(node_osc2, NULL, BAD_CAST "duty", (xmlChar *) double_to_char(sys_param->osc2->duty));
    xmlNewChild(node_osc2, NULL, BAD_CAST "wave", (xmlChar *) double_to_char(sys_param->osc2->wave));

    node_osc3 = xmlNewChild(root_node, NULL, BAD_CAST "osc3", NULL);
    xmlNewChild(node_osc3, NULL, BAD_CAST "onoff", (xmlChar *) double_to_char(sys_param->osc3->onoff));
    xmlNewChild(node_osc3, NULL, BAD_CAST "amp", (xmlChar *) double_to_char(sys_param->osc3->amp));
    xmlNewChild(node_osc3, NULL, BAD_CAST "detune", (xmlChar *) double_to_char(sys_param->osc3->detune));
    xmlNewChild(node_osc3, NULL, BAD_CAST "duty", (xmlChar *) double_to_char(sys_param->osc3->duty));
    xmlNewChild(node_osc3, NULL, BAD_CAST "wave", (xmlChar *) double_to_char(sys_param->osc3->wave));

    node_env = xmlNewChild(root_node, NULL, BAD_CAST "env", NULL);
    xmlNewChild(node_env, NULL, BAD_CAST "attack", (xmlChar *) double_to_char(sys_param->env->attack));
    xmlNewChild(node_env, NULL, BAD_CAST "decay", (xmlChar *) double_to_char(sys_param->env->decay));
    xmlNewChild(node_env, NULL, BAD_CAST "sustain", (xmlChar *) double_to_char(sys_param->env->sustain));
    xmlNewChild(node_env, NULL, BAD_CAST "release", (xmlChar *) double_to_char(sys_param->env->release));

    xmlSaveFormatFileEnc(filename_relat, doc, "UTF-8", 1);

    xmlFreeDoc(doc);

    return 0;
}
