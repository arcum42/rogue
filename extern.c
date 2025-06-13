/*
 * global variable initializaton
 *
 * @(#)extern.c	4.82 (Berkeley) 02/05/99
 *
 * Rogue: Exploring the Dungeons of Doom
 * Copyright (C) 1980-1983, 1985, 1999 Michael Toy, Ken Arnold and Glenn Wichman
 * All rights reserved.
 *
 * See the file LICENSE.TXT for full copyright and licensing information.
 */

#include <stdio.h>
#include <stdbool.h>
#include <curses.h>
#include "rogue.h"

// Global variables
bool after = false;       // True if we want after daemons
bool again = false;       // Repeating the last command
int noscore = 0;          // Was a wizard sometime
bool seenstairs = false;  // Have seen the stairs (for lsd)
bool amulet = false;      // He found the amulet
bool door_stop = false;   // Stop running when we pass a door
bool fight_flush = false; // True if toilet input
bool firstmove = false;   // First move after setting door_stop
bool got_ltc = false;     // We have gotten the local tty chars
bool has_hit = false;     // Has a "hit" message pending in msg
bool in_shell = false;    // True if executing a shell
bool inv_describe = true; // Say which way items are being used
bool jump = false;        // Show running as series of jumps
bool kamikaze = false;    // to_death really to DEATH
bool lower_msg = false;   // Messages should start w/lower case
bool move_on = false;     // Next move shouldn't pick up items
bool msg_esc = false;     // Check for ESC from msg's --More--
bool passgo = false;      // Follow passages
bool playing = true;      // True until he quits
bool q_comm = false;      // Are we executing a 'Q' command?
bool running = false;     // True if player is running
bool save_msg = true;     // Remember last msg
bool see_floor = true;    // Show the lamp illuminated floor
bool stat_msg = false;    // Should status() print as a msg()
bool terse = false;       // True if we should be short
bool to_death = false;    // Fighting is to the death!
bool tombstone = true;    // Print out tombstone at end
#ifdef MASTER
int wizard = false; // True if allows wizard commands
#endif
bool pack_used[26] = {false};

char dir_ch = '\0';                  // Direction from last get_dir() call
char file_name[MAXSTR] = {0};        // Save file name
char huh[MAXSTR] = {0};              // The last message printed
char *p_colors[MAXPOTIONS] = {NULL}; // Colors of the potions
char prbuf[2 * MAXSTR] = {0};        // buffer for sprintfs
char *r_stones[MAXRINGS] = {NULL};   // Stone settings of the rings
char runch = '\0';                   // Direction player is running
char *s_names[MAXSCROLLS] = {NULL};  // Names of the scrolls
char take = '\0';                    // Thing she is taking
char whoami[MAXSTR] = {0};           // Name of player
char *ws_made[MAXSTICKS] = {NULL};   // What sticks are made of
char *ws_type[MAXSTICKS] = {NULL};   // Is it a wand or a staff
int orig_dsusp = 0;                  // Original dsusp char
char fruit[MAXSTR] = "slime-mold";   // Favorite fruit
char home[MAXSTR] = {0};             // User's home directory
char *inv_t_name[] = {
    "Overwrite",
    "Slow",
    "Clear"};
char l_last_comm = '\0'; // Last last_comm
char l_last_dir = '\0';  // Last last_dir
char last_comm = '\0';   // Last command typed
char last_dir = '\0';    // Last direction given
char *tr_name[] = {      // Names of the traps
    "a trapdoor",
    "an arrow trap",
    "a sleeping gas trap",
    "a beartrap",
    "a teleport trap",
    "a poison dart trap",
    "a rust trap",
    "a mysterious trap"};

int n_objs = 0;       // # items listed in inventory() call
int ntraps = 0;       // Number of traps on this level
int hungry_state = 0; // How hungry is he
int inpack = 0;       // Number of things in pack
int inv_type = 0;     // Type of inventory to use
int level = 1;        // What level she is on
int max_hit = 0;      // Max damage done to her in to_death
int max_level = 0;    // Deepest player has gone
int mpos = 0;         // Where cursor is on top line
int no_food = 0;      // Number of levels without food
int a_class[MAXARMORS] = {8, 7, 7, 6, 5, 4, 4, 3};

int count = 0;           // Number of times to repeat command
FILE *scoreboard = NULL; // File descriptor for score file
int food_left = 0;       // Amount of food in hero's stomach
int lastscore = -1;      // Score before this turn
int no_command = 0;      // Number of turns asleep
int no_move = 0;         // Number of turns held in place
int purse = 0;           // How much gold he has
int quiet = 0;           // Number of quiet turns
int vf_hit = 0;          // Number of time flytrap has hit

int dnum = 0; // Dungeon number
int seed = 0; // Random number seed
int e_levels[] = {
    10L, 20L, 40L, 80L, 160L, 320L, 640L, 1300L, 2600L, 5200L,
    13000L, 26000L, 50000L, 100000L, 200000L, 400000L, 800000L,
    2000000L, 4000000L, 8000000L, 0L};

coord delta = {0, 0};  // Change indicated to get_dir()
coord oldpos = {0, 0}; // Position before last look() call
coord stairs = {0, 0}; // Location of staircase

PLACE places[MAXLINES * MAXCOLS] = {0}; // level map

THING *cur_armor = NULL;     // What he is wearing
THING *cur_ring[2] = {NULL}; // Which rings are being worn
THING *cur_weapon = NULL;    // Which weapon he is wielding
THING *l_last_pick = NULL;   // Last last_pick
THING *last_pick = NULL;     // Last object picked in get_item()
THING *lvl_obj = NULL;       // List of objects on this level
THING *mlist = NULL;         // List of monsters on the level
THING player = {0};          // His stats

WINDOW *hw = NULL; // used as a scratch window

#define INIT_STATS {16, 0, 1, 10, 12, "1x4", 12}

struct stats max_stats = INIT_STATS; // The maximum for the player

struct room *oldrp = NULL;         // Roomin(&oldpos)
struct room rooms[MAXROOMS] = {0}; // One for each room -- A level
struct room passages[MAXPASS] = {
    [0 ...(MAXPASS - 1)] = {{0, 0}, {0, 0}, {0, 0}, 0, ISGONE | ISDARK, 0, {{0, 0}}}};

struct monster monsters[26] = {
    {"aquator", 0, ISMEAN, {10, 20, 5, 2, 1, "0x0/0x0"}},
    {"bat", 0, ISFLY, {10, 1, 1, 3, 1, "1x2"}},
    {"centaur", 15, 0, {10, 17, 4, 4, 1, "1x2/1x5/1x5"}},
    {"dragon", 100, ISMEAN, {10, 5000, 10, -1, 1, "1x8/1x8/3x10"}},
    {"emu", 0, ISMEAN, {10, 2, 1, 7, 1, "1x2"}},
    {"venus flytrap", 0, ISMEAN, {10, 80, 8, 3, 1, "%%%x0"}},
    {"griffin", 20, ISMEAN | ISFLY | ISREGEN, {10, 2000, 13, 2, 1, "4x3/3x5"}},
    {"hobgoblin", 0, ISMEAN, {10, 3, 1, 5, 1, "1x8"}},
    {"ice monster", 0, 0, {10, 5, 1, 9, 1, "0x0"}},
    {"jabberwock", 70, 0, {10, 3000, 15, 6, 1, "2x12/2x4"}},
    {"kestrel", 0, ISMEAN | ISFLY, {10, 1, 1, 7, 1, "1x4"}},
    {"leprechaun", 0, 0, {10, 10, 3, 8, 1, "1x1"}},
    {"medusa", 40, ISMEAN, {10, 200, 8, 2, 1, "3x4/3x4/2x5"}},
    {"nymph", 100, 0, {10, 37, 3, 9, 1, "0x0"}},
    {"orc", 15, ISGREED, {10, 5, 1, 6, 1, "1x8"}},
    {"phantom", 0, ISINVIS, {10, 120, 8, 3, 1, "4x4"}},
    {"quagga", 0, ISMEAN, {10, 15, 3, 3, 1, "1x5/1x5"}},
    {"rattlesnake", 0, ISMEAN, {10, 9, 2, 3, 1, "1x6"}},
    {"snake", 0, ISMEAN, {10, 2, 1, 5, 1, "1x3"}},
    {"troll", 50, ISREGEN | ISMEAN, {10, 120, 6, 4, 1, "1x8/1x8/2x6"}},
    {"black unicorn", 0, ISMEAN, {10, 190, 7, -2, 1, "1x9/1x9/2x9"}},
    {"vampire", 20, ISREGEN | ISMEAN, {10, 350, 8, 1, 1, "1x10"}},
    {"wraith", 0, 0, {10, 55, 5, 4, 1, "1x6"}},
    {"xeroc", 30, 0, {10, 100, 7, 7, 1, "4x4"}},
    {"yeti", 30, 0, {10, 50, 4, 6, 1, "1x6/1x6"}},
    {"zombie", 0, ISMEAN, {10, 6, 2, 8, 1, "1x8"}}};

struct obj_info things[NUMTHINGS] = {
    {0, 26}, // potion
    {0, 36}, // scroll
    {0, 16}, // food
    {0, 7},  // weapon
    {0, 7},  // armor
    {0, 4},  // ring
    {0, 4},  // stick
};

struct obj_info arm_info[MAXARMORS] = {
    {"leather armor", 20, 20, NULL, false},
    {"ring mail", 15, 25, NULL, false},
    {"studded leather armor", 15, 20, NULL, false},
    {"scale mail", 13, 30, NULL, false},
    {"chain mail", 12, 75, NULL, false},
    {"splint mail", 10, 80, NULL, false},
    {"banded mail", 10, 90, NULL, false},
    {"plate mail", 5, 150, NULL, false},
};
struct obj_info pot_info[MAXPOTIONS] = {
    {"confusion", 7, 5, NULL, false},
    {"hallucination", 8, 5, NULL, false},
    {"poison", 8, 5, NULL, false},
    {"gain strength", 13, 150, NULL, false},
    {"see invisible", 3, 100, NULL, false},
    {"healing", 13, 130, NULL, false},
    {"monster detection", 6, 130, NULL, false},
    {"magic detection", 6, 105, NULL, false},
    {"raise level", 2, 250, NULL, false},
    {"extra healing", 5, 200, NULL, false},
    {"haste self", 5, 190, NULL, false},
    {"restore strength", 13, 130, NULL, false},
    {"blindness", 5, 5, NULL, false},
    {"levitation", 6, 75, NULL, false},
};
struct obj_info ring_info[MAXRINGS] = {
    {"protection", 9, 400, NULL, false},
    {"add strength", 9, 400, NULL, false},
    {"sustain strength", 5, 280, NULL, false},
    {"searching", 10, 420, NULL, false},
    {"see invisible", 10, 310, NULL, false},
    {"adornment", 1, 10, NULL, false},
    {"aggravate monster", 10, 10, NULL, false},
    {"dexterity", 8, 440, NULL, false},
    {"increase damage", 8, 400, NULL, false},
    {"regeneration", 4, 460, NULL, false},
    {"slow digestion", 9, 240, NULL, false},
    {"teleportation", 5, 30, NULL, false},
    {"stealth", 7, 470, NULL, false},
    {"maintain armor", 5, 380, NULL, false},
};
struct obj_info scr_info[MAXSCROLLS] = {
    {"monster confusion", 7, 140, NULL, false},
    {"magic mapping", 4, 150, NULL, false},
    {"hold monster", 2, 180, NULL, false},
    {"sleep", 3, 5, NULL, false},
    {"enchant armor", 7, 160, NULL, false},
    {"identify potion", 10, 80, NULL, false},
    {"identify scroll", 10, 80, NULL, false},
    {"identify weapon", 6, 80, NULL, false},
    {"identify armor", 7, 100, NULL, false},
    {"identify ring, wand or staff", 10, 115, NULL, false},
    {"scare monster", 3, 200, NULL, false},
    {"food detection", 2, 60, NULL, false},
    {"teleportation", 5, 165, NULL, false},
    {"enchant weapon", 8, 150, NULL, false},
    {"create monster", 4, 75, NULL, false},
    {"remove curse", 7, 105, NULL, false},
    {"aggravate monsters", 3, 20, NULL, false},
    {"protect armor", 2, 250, NULL, false},
};
struct obj_info weap_info[MAXWEAPONS + 1] = {
    {"mace", 11, 8, NULL, false},
    {"long sword", 11, 15, NULL, false},
    {"short bow", 12, 15, NULL, false},
    {"arrow", 12, 1, NULL, false},
    {"dagger", 8, 3, NULL, false},
    {"two handed sword", 10, 75, NULL, false},
    {"dart", 12, 2, NULL, false},
    {"shuriken", 12, 5, NULL, false},
    {"spear", 12, 5, NULL, false},
    {NULL, 0}, // DO NOT REMOVE: fake entry for dragon's breath
};
struct obj_info ws_info[MAXSTICKS] = {
    {"light", 12, 250, NULL, false},
    {"invisibility", 6, 5, NULL, false},
    {"lightning", 3, 330, NULL, false},
    {"fire", 3, 330, NULL, false},
    {"cold", 3, 330, NULL, false},
    {"polymorph", 15, 310, NULL, false},
    {"magic missile", 10, 170, NULL, false},
    {"haste monster", 10, 5, NULL, false},
    {"slow monster", 11, 350, NULL, false},
    {"drain life", 9, 300, NULL, false},
    {"nothing", 1, 5, NULL, false},
    {"teleport away", 6, 340, NULL, false},
    {"teleport to", 6, 50, NULL, false},
    {"cancellation", 5, 280, NULL, false},
};

struct h_list helpstr[] = {
    {'?', "\tprints help", true},
    {'/', "\tidentify object", true},
    {'h', "\tleft", true},
    {'j', "\tdown", true},
    {'k', "\tup", true},
    {'l', "\tright", true},
    {'y', "\tup & left", true},
    {'u', "\tup & right", true},
    {'b', "\tdown & left", true},
    {'n', "\tdown & right", true},
    {'H', "\trun left", false},
    {'J', "\trun down", false},
    {'K', "\trun up", false},
    {'L', "\trun right", false},
    {'Y', "\trun up & left", false},
    {'U', "\trun up & right", false},
    {'B', "\trun down & left", false},
    {'N', "\trun down & right", false},
    {CTRL('H'), "\trun left until adjacent", false},
    {CTRL('J'), "\trun down until adjacent", false},
    {CTRL('K'), "\trun up until adjacent", false},
    {CTRL('L'), "\trun right until adjacent", false},
    {CTRL('Y'), "\trun up & left until adjacent", false},
    {CTRL('U'), "\trun up & right until adjacent", false},
    {CTRL('B'), "\trun down & left until adjacent", false},
    {CTRL('N'), "\trun down & right until adjacent", false},
    {'\0', "\t<SHIFT><dir>: run that way", true},
    {'\0', "\t<CTRL><dir>: run till adjacent", true},
    {'f', "<dir>\tfight till death or near death", true},
    {'t', "<dir>\tthrow something", true},
    {'m', "<dir>\tmove onto without picking up", true},
    {'z', "<dir>\tzap a wand in a direction", true},
    {'^', "<dir>\tidentify trap type", true},
    {'s', "\tsearch for trap/secret door", true},
    {'>', "\tgo down a staircase", true},
    {'<', "\tgo up a staircase", true},
    {'.', "\trest for a turn", true},
    {',', "\tpick something up", true},
    {'i', "\tinventory", true},
    {'I', "\tinventory single item", true},
    {'q', "\tquaff potion", true},
    {'r', "\tread scroll", true},
    {'e', "\teat food", true},
    {'w', "\twield a weapon", true},
    {'W', "\twear armor", true},
    {'T', "\ttake armor off", true},
    {'P', "\tput on ring", true},
    {'R', "\tremove ring", true},
    {'d', "\tdrop object", true},
    {'c', "\tcall object", true},
    {'a', "\trepeat last command", true},
    {')', "\tprint current weapon", true},
    {']', "\tprint current armor", true},
    {'=', "\tprint current rings", true},
    {'@', "\tprint current stats", true},
    {'D', "\trecall what's been discovered", true},
    {'o', "\texamine/set options", true},
    {CTRL('R'), "\tredraw screen", true},
    {CTRL('P'), "\trepeat last message", true},
    {ESCAPE, "\tcancel command", true},
    {'S', "\tsave game", true},
    {'Q', "\tquit", true},
    {'!', "\tshell escape", true},
    {'F', "<dir>\tfight till either of you dies", true},
    {'v', "\tprint version number", true},
    {0, NULL, false}};
