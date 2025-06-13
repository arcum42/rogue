/*
 * Contains functions for dealing with things that happen in the
 * future.
 *
 * @(#)daemon.c	4.7 (Berkeley) 02/05/99
 *
 * Rogue: Exploring the Dungeons of Doom
 * Copyright (C) 1980-1983, 1985, 1999 Michael Toy, Ken Arnold and Glenn Wichman
 * All rights reserved.
 *
 * See the file LICENSE.TXT for full copyright and licensing information.
 */

#include <stddef.h> // for size_t, NULL
#include <curses.h>
#include "rogue.h"

#define EMPTY 0
#define DAEMON -1
#define MAXDAEMONS 20

#define _X_ {EMPTY}

typedef void (*delayed_func_t)(int);

struct delayed_action d_list[MAXDAEMONS] = {
    _X_,
    _X_,
    _X_,
    _X_,
    _X_,
    _X_,
    _X_,
    _X_,
    _X_,
    _X_,
    _X_,
    _X_,
    _X_,
    _X_,
    _X_,
    _X_,
    _X_,
    _X_,
    _X_,
    _X_,
};

/*
 * d_slot:
 *     Find an empty slot in the daemon/fuse list
 */
static struct delayed_action *
d_slot(void)
{
    for (size_t i = 0; i < MAXDAEMONS; ++i)
        if (d_list[i].d_type == EMPTY)
            return &d_list[i];
#ifdef MASTER
    debug("Ran out of fuse slots");
#endif
    return NULL;
}

/*
 * find_slot:
 *     Find a particular slot in the table
 */
static struct delayed_action *
find_slot(delayed_func_t func)
{
    for (size_t i = 0; i < MAXDAEMONS; ++i)
        if (d_list[i].d_type != EMPTY && func == d_list[i].d_func)
            return &d_list[i];
    return NULL;
}

/*
 * start_daemon:
 *     Start a daemon, takes a function.
 */
void start_daemon(delayed_func_t func, int arg, int type)
{
    struct delayed_action *dev = d_slot();
    if (dev == NULL)
        return;
    dev->d_type = type;
    dev->d_func = func;
    dev->d_arg = arg;
    dev->d_time = DAEMON;
}

/*
 * kill_daemon:
 *     Remove a daemon from the list
 */
void kill_daemon(delayed_func_t func)
{
    struct delayed_action *dev = find_slot(func);
    if (dev == NULL)
        return;
    dev->d_type = EMPTY;
}

/*
 * do_daemons:
 *     Run all the daemons that are active with the current flag,
 *     passing the argument to the function.
 */
void do_daemons(int flag)
{
    for (size_t i = 0; i < MAXDAEMONS; ++i)
        if (d_list[i].d_type == flag && d_list[i].d_time == DAEMON)
            d_list[i].d_func(d_list[i].d_arg);
}

/*
 * fuse:
 *     Start a fuse to go off in a certain number of turns
 */
void fuse(delayed_func_t func, int arg, int time, int type)
{
    struct delayed_action *wire = d_slot();
    if (wire == NULL)
        return;
    wire->d_type = type;
    wire->d_func = func;
    wire->d_arg = arg;
    wire->d_time = time;
}

/*
 * lengthen:
 *     Increase the time until a fuse goes off
 */
void lengthen(delayed_func_t func, int xtime)
{
    struct delayed_action *wire = find_slot(func);
    if (wire == NULL)
        return;
    wire->d_time += xtime;
}

/*
 * extinguish:
 *     Put out a fuse
 */
void extinguish(delayed_func_t func)
{
    struct delayed_action *wire = find_slot(func);
    if (wire == NULL)
        return;
    wire->d_type = EMPTY;
}

/*
 * do_fuses:
 *     Decrement counters and start needed fuses
 */
void do_fuses(int flag)
{
    for (size_t i = 0; i < MAXDAEMONS; ++i)
        if (flag == d_list[i].d_type && d_list[i].d_time > 0 && --d_list[i].d_time == 0)
        {
            d_list[i].d_type = EMPTY;
            d_list[i].d_func(d_list[i].d_arg);
        }
}
