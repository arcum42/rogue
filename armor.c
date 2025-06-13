/*
 * This file contains misc functions for dealing with armor
 * @(#)armor.c	4.14 (Berkeley) 02/05/99
 *
 * Rogue: Exploring the Dungeons of Doom
 * Copyright (C) 1980-1983, 1985, 1999 Michael Toy, Ken Arnold and Glenn Wichman
 * All rights reserved.
 *
 * See the file LICENSE.TXT for full copyright and licensing information.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <curses.h>
#include "rogue.h"

enum
{
    MAX_BUFFER_SIZE = 256
};

/*
 * wear:
 *   The player wants to wear something, so let them put it on.
 */
void wear(void)
{
    THING *obj;
    const char *sp;

    obj = get_item("wear", ARMOR);
    if (obj == NULL)
        return;
    if (cur_armor != NULL)
    {
        addmsg("you are already wearing some");
        if (!terse)
            addmsg(".  You'll have to take it off first");
        endmsg();
        after = false;
        return;
    }
    if (obj->o_type != ARMOR)
    {
        msg("you can't wear that");
        return;
    }
    waste_time();
    obj->o_flags |= ISKNOW;
    sp = inv_name(obj, true);
    cur_armor = obj;
    if (!terse)
        addmsg("you are now ");
    msg("wearing %s", sp);
}

/*
 * take_off:
 *   Get the armor off of the player's back
 */
void take_off(void)
{
    THING *obj;

    obj = cur_armor;
    if (obj == NULL)
    {
        after = false;
        if (terse)
            msg("not wearing armor");
        else
            msg("you aren't wearing any armor");
        return;
    }
    if (!dropcheck(cur_armor))
        return;
    cur_armor = NULL;
    if (terse)
        addmsg("was");
    else
        addmsg("you used to be");
    msg(" wearing %c) %s", obj->o_packch, inv_name(obj, true));
}

/*
 * waste_time:
 *   Do nothing but let other things happen
 */
void waste_time(void)
{
    do_daemons(BEFORE);
    do_fuses(BEFORE);
    do_daemons(AFTER);
    do_fuses(AFTER);
}

// Use safer string copy
void copy_string(char *dest, const char *src, size_t size)
{
    if (dest != NULL && src != NULL && size > 0)
    {
        strncpy(dest, src, size - 1);
        dest[size - 1] = '\0';
    }
}

// Example function modernization:
void print_message(const char *message)
{
    if (message != NULL)
    {
        printf("%s\n", message);
    }
}
