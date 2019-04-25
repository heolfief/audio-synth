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
    char filename_relat_alternate[30] = "presets/";

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
        printf("Retying with alternate path : \n");
        strcat(filename_relat_alternate, filename);

        // retry parse XML file with alternate path
        doc = xmlParseFile(filename_relat_alternate);

        if (doc == NULL)
        {
            sys_print_error("Cannot parse preset file");
            return -1;
        }
        printf("Preset found.\n");
    }

    // Load oscillator 1 parameters
    sys_param->osc1->onoff = (OnOff) read_XML_param(doc->xmlosc1->xmlosconoff);
    sys_param->osc1->amp = (Uint16) read_XML_param(doc->xmlosc1->xmloscamp);
    sys_param->osc1->detune = (Sint8) read_XML_param(doc->xmlosc1->xmloscdetune);
    sys_param->osc1->duty = (Uint8) read_XML_param(doc->xmlosc1->xmloscduty);
    sys_param->osc1->wave = (Waveform) read_XML_param(doc->xmlosc1->xmloscwave);

    // Load oscillator 2 parameters
    sys_param->osc2->onoff = (OnOff) read_XML_param(doc->xmlosc2->xmlosconoff);
    sys_param->osc2->amp = (Uint16) read_XML_param(doc->xmlosc2->xmloscamp);
    sys_param->osc2->detune = (Sint8) read_XML_param(doc->xmlosc2->xmloscdetune);
    sys_param->osc2->duty = (Uint8) read_XML_param(doc->xmlosc2->xmloscduty);
    sys_param->osc2->wave = (Waveform) read_XML_param(doc->xmlosc2->xmloscwave);

    // Load oscillator 3 parameters
    sys_param->osc3->onoff = (OnOff) read_XML_param(doc->xmlosc3->xmlosconoff);
    sys_param->osc3->amp = (Uint16) read_XML_param(doc->xmlosc3->xmloscamp);
    sys_param->osc3->detune = (Sint8) read_XML_param(doc->xmlosc3->xmloscdetune);
    sys_param->osc3->duty = (Uint8) read_XML_param(doc->xmlosc3->xmloscduty);
    sys_param->osc3->wave = (Waveform) read_XML_param(doc->xmlosc3->xmloscwave);

    // Load envelope parameters
    sys_param->env->attack = (double) read_XML_param(doc->xmlenv->xmlenvattack);
    sys_param->env->decay = (double) read_XML_param(doc->xmlenv->xmlenvdecay);
    sys_param->env->sustain = (double) read_XML_param(doc->xmlenv->xmlenvsustain);
    sys_param->env->release = (double) read_XML_param(doc->xmlenv->xmlenvrelease);

    // Load flanger parameters
    sys_param->flanger_param->onoff = (OnOff) read_XML_param(doc->xmlflanger->xmlflangonoff);
    sys_param->flanger_param->lfo_wave = (Waveform) read_XML_param(doc->xmlflanger->xmlflanglfowave);
    sys_param->flanger_param->lfo_freq = (double) read_XML_param(doc->xmlflanger->xmlflanglfofreq);
    sys_param->flanger_param->lfo_range = (Uint8) read_XML_param(doc->xmlflanger->xmlflanglforange);
    sys_param->flanger_param->delay = (double) read_XML_param(doc->xmlflanger->xmlflangdelay);
    sys_param->flanger_param->depth = (Uint8) read_XML_param(doc->xmlflanger->xmlflangdepth);

    // Load amp mod parameters
    sys_param->amp_mod_param->onoff = (OnOff) read_XML_param(doc->xmlampmod->xmlmodonoff);
    sys_param->amp_mod_param->mod_level = (Uint8) read_XML_param(doc->xmlampmod->xmlmodlevel);
    sys_param->amp_mod_param->freq = (double) read_XML_param(doc->xmlampmod->xmlmodfreq);
    sys_param->amp_mod_param->wave = (Waveform) read_XML_param(doc->xmlampmod->xmlmodwave);
    sys_param->amp_mod_param->duty = (Uint8) read_XML_param(doc->xmlampmod->xmlmodduty);

    // Load distortion parameters
    sys_param->dist_param->onoff = (OnOff) read_XML_param(doc->xmldist->xmldistonoff);
    sys_param->dist_param->dist_level = (Uint8) read_XML_param(doc->xmldist->xmldistlevel);
    sys_param->dist_param->wet = (Uint8) read_XML_param(doc->xmldist->xmldistwet);

    // Load LFO filter parameters
    sys_param->lfo_filter_param->onoff = (OnOff) read_XML_param(doc->xmllfofilt->xmllfofiltonoff);
    sys_param->lfo_filter_param->filter_type = (Filter_type) read_XML_param(doc->xmllfofilt->xmllfofiltfilttype);
    sys_param->lfo_filter_param->filter_freq = (Uint16) read_XML_param(doc->xmllfofilt->xmllfofiltfiltfreq);
    sys_param->lfo_filter_param->lfo_freq = (double) read_XML_param(doc->xmllfofilt->xmllfofiltlfofreq);
    sys_param->lfo_filter_param->resonance = (double) read_XML_param(doc->xmllfofilt->xmllfofiltresonance);
    sys_param->lfo_filter_param->wave = (Waveform) read_XML_param(doc->xmllfofilt->xmllfofiltwave);
    sys_param->lfo_filter_param->duty = (Uint8) read_XML_param(doc->xmllfofilt->xmllfofiltduty);
    sys_param->lfo_filter_param->filter_excursion = (Uint16) read_XML_param(doc->xmllfofilt->xmllfofiltfilterexcurs);

    // Load filter parameters
    sys_param->filter_param->onoff = (OnOff) read_XML_param(doc->xmlfilt->xmlfiltonoff);
    sys_param->filter_param->filter_type = (Filter_type) read_XML_param(doc->xmlfilt->xmlfiltfiltertype);
    sys_param->filter_param->cutoff_freq = (Uint16) read_XML_param(doc->xmlfilt->xmlfiltcutofffreq);
    sys_param->filter_param->resonance = (double) read_XML_param(doc->xmlfilt->xmlfiltresonance);

    // Load Delay parameters
    sys_param->delay_param->onoff = (OnOff) read_XML_param(doc->xmldelay->xmldelayonoff);
    sys_param->delay_param->delay = (double) read_XML_param(doc->xmldelay->xmldelaydelay);
    sys_param->delay_param->feedback = (Uint8) read_XML_param(doc->xmldelay->xmldelayfeedback);

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
    xmlNodePtr root_node, node_osc1, node_osc2, node_osc3, node_env, node_filter, node_dist, node_amp_mod, node_flanger,
        node_lfo_filter, node_delay;

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

    node_flanger = xmlNewChild(root_node, NULL, BAD_CAST "flanger", NULL);
    xmlNewChild(node_flanger, NULL, BAD_CAST "onoff", (xmlChar *) double_to_char(sys_param->flanger_param->onoff));
    xmlNewChild(node_flanger, NULL, BAD_CAST "lfowave", (xmlChar *) double_to_char(sys_param->flanger_param->lfo_wave));
    xmlNewChild(node_flanger, NULL, BAD_CAST "lfofreq", (xmlChar *) double_to_char(sys_param->flanger_param->lfo_freq));
    xmlNewChild(node_flanger, NULL, BAD_CAST "lforange", (xmlChar *) double_to_char(sys_param->flanger_param->lfo_range));
    xmlNewChild(node_flanger, NULL, BAD_CAST "delay", (xmlChar *) double_to_char(sys_param->flanger_param->delay));
    xmlNewChild(node_flanger, NULL, BAD_CAST "depth", (xmlChar *) double_to_char(sys_param->flanger_param->depth));

    node_amp_mod = xmlNewChild(root_node, NULL, BAD_CAST "amp_mod", NULL);
    xmlNewChild(node_amp_mod, NULL, BAD_CAST "onoff", (xmlChar *) double_to_char(sys_param->amp_mod_param->onoff));
    xmlNewChild(node_amp_mod, NULL, BAD_CAST "mod_level", (xmlChar *) double_to_char(sys_param->amp_mod_param->mod_level));
    xmlNewChild(node_amp_mod, NULL, BAD_CAST "freq", (xmlChar *) double_to_char(sys_param->amp_mod_param->freq));
    xmlNewChild(node_amp_mod, NULL, BAD_CAST "wave", (xmlChar *) double_to_char(sys_param->amp_mod_param->wave));
    xmlNewChild(node_amp_mod, NULL, BAD_CAST "duty", (xmlChar *) double_to_char(sys_param->amp_mod_param->duty));

    node_dist = xmlNewChild(root_node, NULL, BAD_CAST "distortion", NULL);
    xmlNewChild(node_dist, NULL, BAD_CAST "onoff", (xmlChar *) double_to_char(sys_param->dist_param->onoff));
    xmlNewChild(node_dist, NULL, BAD_CAST "dist_level", (xmlChar *) double_to_char(sys_param->dist_param->dist_level));
    xmlNewChild(node_dist, NULL, BAD_CAST "wet", (xmlChar *) double_to_char(sys_param->dist_param->wet));

    node_lfo_filter = xmlNewChild(root_node, NULL, BAD_CAST "lfo_filter", NULL);
    xmlNewChild(node_lfo_filter, NULL, BAD_CAST "onoff", (xmlChar *) double_to_char(sys_param->lfo_filter_param->onoff));
    xmlNewChild(node_lfo_filter, NULL, BAD_CAST "filter_type", (xmlChar *) double_to_char(sys_param->lfo_filter_param->filter_type));
    xmlNewChild(node_lfo_filter, NULL, BAD_CAST "filter_freq", (xmlChar *) double_to_char(sys_param->lfo_filter_param->filter_freq));
    xmlNewChild(node_lfo_filter, NULL, BAD_CAST "lfo_freq", (xmlChar *) double_to_char(sys_param->lfo_filter_param->lfo_freq));
    xmlNewChild(node_lfo_filter, NULL, BAD_CAST "resonance", (xmlChar *) double_to_char(sys_param->lfo_filter_param->resonance));
    xmlNewChild(node_lfo_filter, NULL, BAD_CAST "wave", (xmlChar *) double_to_char(sys_param->lfo_filter_param->wave));
    xmlNewChild(node_lfo_filter, NULL, BAD_CAST "duty", (xmlChar *) double_to_char(sys_param->lfo_filter_param->duty));
    xmlNewChild(node_lfo_filter, NULL, BAD_CAST "filter_excursion", (xmlChar *) double_to_char(sys_param->lfo_filter_param->filter_excursion));

    node_filter = xmlNewChild(root_node, NULL, BAD_CAST "filter", NULL);
    xmlNewChild(node_filter, NULL, BAD_CAST "onoff", (xmlChar *) double_to_char(sys_param->filter_param->onoff));
    xmlNewChild(node_filter, NULL, BAD_CAST "filter_type", (xmlChar *) double_to_char(sys_param->filter_param->filter_type));
    xmlNewChild(node_filter, NULL, BAD_CAST "cutoff_freq", (xmlChar *) double_to_char(sys_param->filter_param->cutoff_freq));
    xmlNewChild(node_filter, NULL, BAD_CAST "resonance", (xmlChar *) double_to_char(sys_param->filter_param->resonance));

    node_delay = xmlNewChild(root_node, NULL, BAD_CAST "delay", NULL);
    xmlNewChild(node_delay, NULL, BAD_CAST "onoff", (xmlChar *) double_to_char(sys_param->delay_param->onoff));
    xmlNewChild(node_delay, NULL, BAD_CAST "delay", (xmlChar *) double_to_char(sys_param->delay_param->delay));
    xmlNewChild(node_delay, NULL, BAD_CAST "feedback", (xmlChar *) double_to_char(sys_param->delay_param->feedback));

    xmlSaveFormatFileEnc(filename_relat, doc, "UTF-8", 1);

    xmlFreeDoc(doc);

    return 0;
}
