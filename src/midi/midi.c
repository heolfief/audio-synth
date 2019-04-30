/**
 * \file midi.c
 * \brief MIDI functions implementation.
 *
 *
 * Here are implemented the MIDI related function, for both MIDI files and USB MIDI (from keyboard)
 */
#include "midi.h"

// The following list contains known names for midi peripherals in /dev/
const char *list_of_common_midi_dev[NUMBER_OF_KNOWN_MIDI_DEV] =
    {"admmidi0", "admmidi1", "amidi", "amidi0", "amidi1", "dmmidi0", "dmmidi1", "dmmidi2", "midi", "midi1", "midi2"};

MIDI_PERIPHERAL *open_midi_peripheral()
{
    MIDI_PERIPHERAL *f = NULL;
    char path[20] = "";

    for (int i = 0; i < NUMBER_OF_KNOWN_MIDI_DEV; ++i)
    {
        strcpy(path, "/dev/");
        strcat(path, list_of_common_midi_dev[i]);

        f = fopen(path, "r");
        if (f != NULL)
        {
            fprintf(stdout, "MIDI device %s found. SUCCESS.\n", path);
            return f;
        }
        else
        {
            // fprintf(stdout, "MIDI device %s not found. Trying another.\n", path);
        }
    }

    sys_print_error("No MIDI devices found");
    return NULL;
}

int process_midi_input(MIDI_PERIPHERAL *mp, Core *ac)
{
    Uint8 midi_data[3]; // 0 is status, 1 is note id, 2 is note velocity
    Uint8 midi_status;

    if (mp == NULL)
    {
        sys_print_error("MIDI peripheral is NULL");
        return -1;
    }

    if (ac == NULL)
    {
        sys_print_error("Core parameter is NULL");
        return -1;
    }

    fread(&midi_data, 1, 3, mp);

    midi_status = midi_data[0] >> 4u;

    if (midi_status == 0b1000)
    {
        if (midi_note_OFF(ac, midi_data[1]))return -1;
    }
    if (midi_status == 0b1001)
    {
        if (midi_note_ON(ac, midi_data[1], midi_data[2]))return -1;
    }

    return 0;
}

int midi_note_ON(Core *ac, Uint8 id, Uint8 velo)
{
    int free_note;
    double freq;
    int old_note;

    if (ac == NULL)
    {
        sys_print_error("Core parameter is NULL");
        return -1;
    }

    if (velo > 127)
    {
        sys_print_error("Velocity parameter is out of range");
        return -1;
    }

    freq = get_freq_from_note_nbr(id, (double) MIDI_NOTE_0_FREQ);

    // If note is already ON
    old_note = find_note_from_id(ac->note_array, id);
    if ((old_note != -1) && (ac->note_array[old_note]->onoff == ON))
    {
        sys_print_error("Note is already ON");
        return -1;
    }

    free_note = find_free_note(ac->note_array);
    if (free_note == -1)return -1;

    ac->note_array[free_note]->freq = freq;
    ac->note_array[free_note]->midi_id = id;
    ac->note_array[free_note]->velocity_amp =
        (double) ((double) velo / MAX_MIDI_NOTE_VELOCITY);    // velocity_amp ranges from 0 to 1

    note_on(ac->note_array[free_note]);

    return 0;
}

int midi_note_OFF(Core *ac, Uint8 id)
{
    int note_to_kill;

    if (ac == NULL)
    {
        sys_print_error("Core parameter is NULL");
        return -1;
    }

    note_to_kill = find_note_from_id(ac->note_array, id);

    if (note_to_kill == -1)
    {
        sys_print_error("No note to set to OFF found");
        return -1;
    }

    note_off(ac->note_array[note_to_kill]);

    return 0;
}

MIDI_PERIPHERAL *alloc_midi_peripheral()
{
    MIDI_PERIPHERAL *mp = (MIDI_PERIPHERAL *) malloc(sizeof(MIDI_PERIPHERAL));
    if (mp == NULL)
    {
        sys_print_error("Memory allocation error");
        return NULL;
    }

    return mp;
}

int free_midi_peripheral(MIDI_PERIPHERAL *mp)
{
    free(mp);
    return 0;
}