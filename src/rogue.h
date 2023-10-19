/*
 * Rogue definitions and variable declarations
 *
 * @(#)rogue.h	5.42 (Berkeley) 08/06/83
 *
 * Rogue: Exploring the Dungeons of Doom
 * Copyright (C) 1980-1983, 1985, 1999 Michael Toy, Ken Arnold and Glenn Wichman
 * All rights reserved.
 *
 * See the file LICENSE.TXT for full copyright and licensing information.
 */

#pragma once

#include "extern.h"

#undef lines

#define NOOP(x) (x += 0)
#define CCHAR(x) ((char)(x & A_CHARTEXT))
/*
 * Maximum number of different things
 */
static const int MAXROOMS = 9;
static const int MAXTHINGS = 9;
static const int MAXOBJ = 9;
static const int MAXPACK = 23;
static const int MAXTRAPS = 10;
static const int AMULETLEVEL = 26;
static const int NUMTHINGS = 7; /* number of types of things */
static const int MAXPASS = 13;  /* upper limit on number of passages */
static const int NUMLINES = 24;
static const int NUMCOLS = 80;
static const int STATLINE = (NUMLINES - 1);
static const int BORE_LEVEL = 50;

/*
 * return values for get functions
 */
static const int NORM = 0;  /* normal exit */
static const int QUIT = 1;  /* quit option setting */
static const int MINUS = 2; /* back up one option */

/*
 * inventory types
 */
static const int INV_OVER = 0;
static const int INV_SLOW = 1;
static const int INV_CLEAR = 2;

/*
 * All the fun defines
 */
#define when                                                                   \
  break;                                                                       \
  case
#define otherwise                                                              \
  break;                                                                       \
  default
#define until(expr) while (!(expr))
#define next(ptr) (*ptr).l_next
#define prev(ptr) (*ptr).l_prev
#define winat(y, x) (moat(y, x) != NULL ? moat(y, x)->t_disguise : chat(y, x))
#define ce(a, b) ((a).x == (b).x && (a).y == (b).y)
#define hero player.t_pos
#define pstats player.t_stats
#define pack player.t_pack
#define proom player.t_room
#define max_hp player.t_stats.s_maxhp
#define attach(a, b) _attach(&a, b)
#define detach(a, b) _detach(&a, b)
#define free_list(a) _free_list(&a)
#undef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#define on(thing, flag) ((bool)(((thing).t_flags & (flag)) != 0))
#define GOLDCALC (rnd(50 + 10 * level) + 2)
#define ISRING(h, r) (cur_ring[h] != NULL && cur_ring[h]->o_which == r)
#define ISWEARING(r) (ISRING(LEFT, r) || ISRING(RIGHT, r))
#define ISMULT(type) (type == POTION || type == SCROLL || type == FOOD)
#define INDEX(y, x) (&places[((x) << 5) + (y)])
#define chat(y, x) (places[((x) << 5) + (y)].p_ch)
#define flat(y, x) (places[((x) << 5) + (y)].p_flags)
#define moat(y, x) (places[((x) << 5) + (y)].p_monst)
#define unc(cp) (cp).y, (cp).x
#ifdef MASTER
#define debug                                                                  \
  if (wizard)                                                                  \
  msg
#endif

/*
 * things that appear on the screens
 */
#define PASSAGE '#'
#define DOOR '+'
#define FLOOR '.'
#define PLAYER '@'
#define TRAP '^'
#define STAIRS '%'
#define GOLD '*'
#define POTION '!'
#define SCROLL '?'
#define MAGIC '$'
#define FOOD ':'
#define WEAPON ')'
#define ARMOR ']'
#define AMULET ','
#define RING '='
#define STICK '/'
#define CALLABLE -1
#define R_OR_S -2

/*
 * Various constants
 */
#define BEARTIME spread(3)
#define SLEEPTIME spread(5)
#define HOLDTIME spread(2)
#define WANDERTIME spread(70)
#define BEFORE spread(1)
#define AFTER spread(2)

static const int HEALTIME = 30;
static const int HUHDURATION = 20;
static const int SEEDURATION = 850;
static const int HUNGERTIME = 1300;
static const int MORETIME = 150;
static const int STOMACHSIZE = 2000;
static const int STARVETIME = 850;
static const int ESCAPE = 27;
static const int LEFT = 0;
static const int RIGHT = 1;
static const int BOLT_LENGTH = 6;
static const int LAMPDIST = 3;

#ifdef MASTER
#ifndef PASSWD
#define PASSWD "mTBellIQOsLNA"
#endif
#endif

/*
 * Save against things
 */
static const int VS_POISON = 00;
static const int VS_PARALYZATION = 00;
static const int VS_DEATH = 00;
static const int VS_BREATH = 02;
static const int VS_MAGIC = 03;

/*
 * Various flag bits
 */
/* flags for rooms */
static const int ISDARK = 0000001; /* room is dark */
static const int ISGONE = 0000002; /* room is gone (a corridor) */
static const int ISMAZE = 0000004; /* room is gone (a corridor) */

/* flags for objects */
static const int ISCURSED = 000001; /* object is cursed */
static const int ISKNOW = 0000002;  /* player knows details about the object */
static const int ISMISL = 0000004;  /* object is a missile type */
static const int ISMANY = 0000010;  /* object comes in groups */
/*	ISFOUND 0000020		...is used for both objects and creatures */
static const int ISPROT = 0000040; /* armor is permanently protected */

/* flags for creatures */
static const int CANHUH = 0000001;  /* creature can confuse */
static const int CANSEE = 0000002;  /* creature can see invisible creatures */
static const int ISBLIND = 0000004; /* creature is blind */
static const int ISCANC = 0000010;  /* creature has special qualities cancelled */
static const int ISLEVIT = 0000010; /* hero is levitating */
static const int ISFOUND = 0000020; /* creature has been seen (used for objects) */
static const int ISGREED = 0000040; /* creature runs to protect gold */
static const int ISHASTE = 0000100; /* creature has been hastened */
static const int ISTARGET = 000200; /* creature is the target of an 'f' command */
static const int ISHELD = 0000400;  /* creature has been held */
static const int ISHUH = 0001000;   /* creature is confused */
static const int ISINVIS = 0002000; /* creature is invisible */
static const int ISMEAN = 0004000;  /* creature can wake when player enters room */
static const int ISHALU = 0004000;  /* hero is on acid trip */
static const int ISREGEN = 0010000; /* creature can regenerate */
static const int ISRUN = 0020000;   /* creature is running at the player */
static const int SEEMONST = 040000; /* hero can detect unseen monsters */
static const int ISFLY = 0040000;   /* creature can fly */
static const int ISSLOW = 0100000;  /* creature has been slowed */

/*
 * Flags for level map
 */
static const int F_PASS = 0x80;    /* is a passageway */
static const int F_SEEN = 0x40;    /* have seen this spot before */
static const int F_DROPPED = 0x20; /* object was dropped here */
static const int F_LOCKED = 0x20;  /* door is locked */
static const int F_REAL = 0x10;    /* what you see is what you get */
static const int F_PNUM = 0x0f;    /* passage number mask */
static const int F_TMASK = 0x07;   /* trap number mask */

/*
 * Trap types
 */
static const int T_DOOR = 00;
static const int T_ARROW = 01;
static const int T_SLEEP = 02;
static const int T_BEAR = 03;
static const int T_TELEP = 04;
static const int T_DART = 05;
static const int T_RUST = 06;
static const int T_MYST = 07;
static const int NTRAPS = 8;

/*
 * Potion types
 */
static const int P_CONFUSE = 0;
static const int P_LSD = 1;
static const int P_POISON = 2;
static const int P_STRENGTH = 3;
static const int P_SEEINVIS = 4;
static const int P_HEALING = 5;
static const int P_MFIND = 6;
static const int P_TFIND = 7;
static const int P_RAISE = 8;
static const int P_XHEAL = 9;
static const int P_HASTE = 10;
static const int P_RESTORE = 11;
static const int P_BLIND = 12;
static const int P_LEVIT = 13;
static const int MAXPOTIONS = 14;

/*
 * Scroll types
 */
static const int S_CONFUSE = 0;
static const int S_MAP = 1;
static const int S_HOLD = 2;
static const int S_SLEEP = 3;
static const int S_ARMOR = 4;
static const int S_ID_POTION = 5;
static const int S_ID_SCROLL = 6;
static const int S_ID_WEAPON = 7;
static const int S_ID_ARMOR = 8;
static const int S_ID_R_OR_S = 9;
static const int S_SCARE = 10;
static const int S_FDET = 11;
static const int S_TELEP = 12;
static const int S_ENCH = 13;
static const int S_CREATE = 14;
static const int S_REMOVE = 15;
static const int S_AGGR = 16;
static const int S_PROTECT = 17;
static const int MAXSCROLLS = 18;

/*
 * Weapon types
 */
static const int MACE = 0;
static const int SWORD = 1;
static const int  BOW = 2;
static const int ARROW = 3;
static const int  DAGGER = 4;
static const int TWOSWORD = 5;
static const int DART = 6;
static const int SHIRAKEN = 7;
static const int SPEAR = 8;
static const int FLAME = 9;      /* fake entry for dragon breath (ick) */
static const int MAXWEAPONS = 9; /* this should equal FLAME */

/*
 * Armor types
 */
static const int LEATHER = 0;
static const int RING_MAIL = 1;
static const int STUDDED_LEATHER = 2;
static const int SCALE_MAIL = 3;
static const int CHAIN_MAIL = 4;
static const int SPLINT_MAIL = 5;
static const int BANDED_MAIL = 6;
static const int PLATE_MAIL = 7;
static const int MAXARMORS = 8;

/*
 * Ring types
 */
static const int R_PROTECT = 0;
static const int R_ADDSTR = 1;
static const int R_SUSTSTR = 2;
static const int R_SEARCH = 3;
static const int R_SEEINVIS = 4;
static const int R_NOP = 5;
static const int R_AGGR = 6;
static const int R_ADDHIT = 7;
static const int R_ADDDAM = 8;
static const int R_REGEN = 9;
static const int R_DIGEST = 10;
static const int R_TELEPORT = 11;
static const int R_STEALTH = 12;
static const int R_SUSTARM = 13;
static const int MAXRINGS = 14;

/*
 * Rod/Wand/Staff types
 */
static const int WS_LIGHT = 0;
static const int WS_INVIS = 1;
static const int WS_ELECT = 2;
static const int WS_FIRE = 3;
static const int WS_COLD = 4;
static const int WS_POLYMORPH = 5;
static const int WS_MISSILE = 6;
static const int WS_HASTE_M = 7;
static const int WS_SLOW_M = 8;
static const int WS_DRAIN = 9;
static const int WS_NOP = 10;
static const int WS_TELAWAY = 11;
static const int WS_TELTO = 12;
static const int WS_CANCEL = 13;
static const int MAXSTICKS = 14;

/*
 * Now we define the structures and types
 */

/*
 * Help list
 */
struct h_list {
  char h_ch;
  char *h_desc;
  bool h_print;
};

/*
 * Coordinate data type
 */
typedef struct {
  int x;
  int y;
} coord;

typedef unsigned int str_t;

/*
 * Stuff about objects
 */
struct obj_info {
  char *oi_name;
  int oi_prob;
  int oi_worth;
  char *oi_guess;
  bool oi_know;
};

/*
 * Room structure
 */
struct room {
  coord r_pos;      /* Upper left corner */
  coord r_max;      /* Size of room */
  coord r_gold;     /* Where the gold is */
  int r_goldval;    /* How much the gold is worth */
  short r_flags;    /* info about the room */
  int r_nexits;     /* Number of exits */
  coord r_exit[12]; /* Where the exits are */
};

/*
 * Structure describing a fighting being
 */
struct stats {
  str_t s_str;    /* Strength */
  int s_exp;      /* Experience */
  int s_lvl;      /* level of mastery */
  int s_arm;      /* Armor class */
  int s_hpt;      /* Hit points */
  char s_dmg[13]; /* String describing damage done */
  int s_maxhp;    /* Max hit points */
};

/*
 * Structure for monsters and player
 */
union thing {
  struct {
    union thing *_l_next, *_l_prev; /* Next pointer in link */
    coord _t_pos;                   /* Position */
    bool _t_turn;                   /* If slowed, is it a turn to move */
    char _t_type;                   /* What it is */
    char _t_disguise;               /* What mimic looks like */
    char _t_oldch;                  /* Character that was where it was */
    coord *_t_dest;                 /* Where it is running to */
    short _t_flags;                 /* State word */
    struct stats _t_stats;          /* Physical description */
    struct room *_t_room;           /* Current room for thing */
    union thing *_t_pack;           /* What the thing is carrying */
    int _t_reserved;
  } _t;
  struct {
    union thing *_l_next, *_l_prev; /* Next pointer in link */
    int _o_type;                    /* What kind of object it is */
    coord _o_pos;                   /* Where it lives on the screen */
    char *_o_text;                  /* What it says if you read it */
    int _o_launch;                  /* What you need to launch it */
    char _o_packch;                 /* What character it is in the pack */
    char _o_damage[8];              /* Damage if used like sword */
    char _o_hurldmg[8];             /* Damage if thrown */
    int _o_count;                   /* count for plural objects */
    int _o_which;                   /* Which object of a type it is */
    int _o_hplus;                   /* Plusses to hit */
    int _o_dplus;                   /* Plusses to damage */
    int _o_arm;                     /* Armor protection */
    int _o_flags;                   /* information about objects */
    int _o_group;                   /* group number for this object */
    char *_o_label;                 /* Label for object */
  } _o;
};

typedef union thing THING;

#define l_next _t._l_next
#define l_prev _t._l_prev
#define t_pos _t._t_pos
#define t_turn _t._t_turn
#define t_type _t._t_type
#define t_disguise _t._t_disguise
#define t_oldch _t._t_oldch
#define t_dest _t._t_dest
#define t_flags _t._t_flags
#define t_stats _t._t_stats
#define t_pack _t._t_pack
#define t_room _t._t_room
#define t_reserved _t._t_reserved
#define o_type _o._o_type
#define o_pos _o._o_pos
#define o_text _o._o_text
#define o_launch _o._o_launch
#define o_packch _o._o_packch
#define o_damage _o._o_damage
#define o_hurldmg _o._o_hurldmg
#define o_count _o._o_count
#define o_which _o._o_which
#define o_hplus _o._o_hplus
#define o_dplus _o._o_dplus
#define o_arm _o._o_arm
#define o_charges o_arm
#define o_goldval o_arm
#define o_flags _o._o_flags
#define o_group _o._o_group
#define o_label _o._o_label

/*
 * describe a place on the level map
 */
typedef struct {
  char p_ch;
  char p_flags;
  THING *p_monst;
} PLACE;

/*
 * Array containing information on all the various types of monsters
 */
struct monster {
  char *m_name;         /* What to call the monster */
  int m_carry;          /* Probability of carrying something */
  short m_flags;        /* things about the monster */
  struct stats m_stats; /* Initial stats */
};

/*
 * External variables
 */

extern bool after, again, allscore, amulet, door_stop, fight_flush, firstmove,
    has_hit, inv_describe, jump, kamikaze, lower_msg, move_on, msg_esc,
    pack_used[], passgo, playing, q_comm, running, save_msg, see_floor,
    seenstairs, stat_msg, terse, to_death, tombstone;

extern char dir_ch, file_name[], home[], huh[], *inv_t_name[], l_last_comm,
    l_last_dir, last_comm, last_dir, *Numname, outbuf[], *p_colors[],
    *r_stones[], *release, runch, *s_names[], take, *tr_name[], *ws_made[],
    *ws_type[];

extern int a_class[], count, food_left, hungry_state, inpack, inv_type,
    lastscore, level, max_hit, max_level, mpos, n_objs, no_command, no_food,
    no_move, noscore, ntraps, purse, quiet, vf_hit;

extern unsigned int numscores;

extern int dnum, e_levels[], seed;

extern WINDOW *hw;

extern coord delta, oldpos, stairs;

extern PLACE places[];

extern THING *cur_armor, *cur_ring[], *cur_weapon, *l_last_pick, *last_pick,
    *lvl_obj, *mlist, player;

extern struct h_list helpstr[];

extern struct room *oldrp, passages[], rooms[];

extern struct stats max_stats;

extern struct monster monsters[];

extern struct obj_info arm_info[], pot_info[], ring_info[], scr_info[],
    things[], ws_info[], weap_info[];

/*
 * Function types
 */
void _attach(THING **list, THING *item);
void _detach(THING **list, THING *item);
void _free_list(THING **ptr);
void addmsg(char *fmt, ...);
bool add_haste(bool potion);
void add_pack(THING *obj, bool silent);
void add_pass();
void add_str(str_t *sp, int amt);
void accnt_maze(int y, int x, int ny, int nx);
void aggravate();
int attack(THING *mp);
void badcheck(char *name, struct obj_info *info, int bound);
void bounce(THING *weap, char *mname, bool noend);
void call();
void call_it(struct obj_info *info);
bool cansee(int y, int x);
int center(char *str);
void chg_str(int amt);
void check_level();
void conn(int r1, int r2);
void command();
void create_obj();

void current(THING *cur, char *how, char *where);
void d_level();
void death(char monst);
char death_monst();
void dig(int y, int x);
void discard(THING *item);
void discovered();
int dist(int y1, int x1, int y2, int x2);
int dist_cp(coord *c1, coord *c2);
int do_chase(THING *th);
void do_daemons(int flag);
void do_fuses(int flag);
void do_maze(struct room *rp);
void do_motion(THING *obj, int ydelta, int xdelta);
void do_move(int dy, int dx);
void do_passages();
void do_pot(int type, bool knowit);
void do_rooms();
void do_run(char ch);
void do_zap();
void doadd(char *fmt, va_list args);
void door(struct room *rm, coord *cp);
void door_open(struct room *rp);
void drain();
void draw_room(struct room *rp);
void drop();
void eat();
size_t encread(char *start, size_t size, FILE *inf);
size_t encwrite(char *start, size_t size, FILE *outf);
int endmsg();
void enter_room(coord *cp);
void erase_lamp(coord *pos, struct room *rp);
int exp_add(THING *tp);
void extinguish(void (*func)());
void fall(THING *obj, bool pr);
void fire_bolt(coord *start, coord *dir, char *name);
char floor_at();
void flush_type();
int fight(coord *mp, THING *weap, bool thrown);
void fix_stick(THING *cur);
void fuse(void (*func)(), int arg, int time, int type);
bool get_dir();
int gethand();
void give_pack(THING *tp);
void help();
void hit(char *er, char *ee, bool noend);
void horiz(struct room *rp, int starty);
void leave_room(coord *cp);
void lengthen(void (*func)(), int xtime);
void look(bool wakeup);
int hit_monster(int y, int x, THING *obj);
void identify();
void illcom(int ch);
void init_check();
void init_colors();
void init_materials();
void init_names();
void init_player();
void init_probs();
void init_stones();
void init_weapon(THING *weap, int which);
bool inventory(THING *list, int type);
void invis_on();
void killed(THING *tp, bool pr);
void kill_daemon(void (*func)());
bool lock_sc();
void miss(char *er, char *ee, bool noend);
void missile(int ydelta, int xdelta);
void money(int value);
int move_monst(THING *tp);
void move_msg(THING *obj);
int msg(char *fmt, ...);
void nameit(THING *obj, char *type, char *which, struct obj_info *op,
            char *(*prfunc)(THING *));
void new_level();
void new_monster(THING *tp, char type, coord *cp);
void numpass(int y, int x);
void option();
void open_score();
void parse_opts(char *str);
void passnum();
char *pick_color(char *col);
int pick_one(struct obj_info *info, int nitems);
void pick_up(char ch);
void picky_inven();
void pr_spec(struct obj_info *info, int nitems);
void pr_list();
void put_bool(void *b);
void put_inv_t(void *ip);
void put_str(void *str);
void put_things();
void putpass(coord *cp);
void quaff();
void raise_level();
char randmonster(bool wander);
void read_scroll();
void relocate(THING *th, coord *new_loc);
void remove_mon(coord *mp, THING *tp, bool waskill);
void reset_last();
bool restore(char *file, char **envp);
int ring_eat(int hand);
void ring_on();
void ring_off();
int rnd(int range);
int rnd_room();
int roll(int number, int sides);
int rs_save_file(FILE *savef);
int rs_restore_file(FILE *inf);
void runto(coord *runner);
void rust_armor(THING *arm);
int save(int which);
void save_file(FILE *savef);
void save_game();
int save_throw(int which, THING *tp);
void score(int amount, int flags, char monst);
void search();
void set_know(THING *obj, struct obj_info *info);
void set_oldch(THING *tp, coord *cp);
void setup();
void shell();
bool show_floor();
void show_map();
void show_win(char *message);
int sign(int nm);
int spread(int nm);
void start_daemon(void (*func)(), int arg, int type);
void start_score();
void status();
int step_ok(int ch);
void strucpy(char *s1, char *s2, int len);
int swing(int at_lvl, int op_arm, int wplus);
void take_off();
void teleport();
void total_winner();
void thunk(THING *weap, char *mname, bool noend);
void treas_room();
void turnref();
void u_level();
void uncurse(THING *obj);
void unlock_sc();
void vert(struct room *rp, int startx);
void wait_for(int ch);
THING *wake_monster(int y, int x);
void wanderer();
void waste_time();
void wear();
void whatis(bool insist, int type);
void wield();

bool chase(THING *tp, coord *ee);
bool diag_ok(coord *sp, coord *ep);
bool dropcheck(THING *obj);
bool fallpos(coord *pos, coord *newpos);
bool find_floor(struct room *rp, coord *cp, int limit, bool monst);
bool is_magic(THING *obj);
bool is_symlink(char *sp);
bool levit_check();
bool pack_room(bool from_floor, THING *obj);
bool roll_em(THING *thatt, THING *thdef, THING *weap, bool hurl);
bool see_monst(THING *mp);
bool seen_stairs();
bool turn_ok(int y, int x);
bool turn_see(bool turn_off);
bool is_current(THING *obj);
int passwd();

char be_trapped(coord *tc);
char floor_ch();
char pack_char();
char readchar();
char rnd_thing();

char *charge_str(THING *obj);
char *choose_str(char *ts, char *ns);
char *inv_name(THING *obj, bool drop);
char *nullstr(THING *ignored);
char *num(int n1, int n2, char type);
char *ring_num(THING *obj);
char *set_mname(THING *tp);
char *vowelstr(char *str);

int get_bool(void *vp, WINDOW *win);
int get_inv_t(void *vp, WINDOW *win);
int get_num(void *vp, WINDOW *win);
int get_sf(void *vp, WINDOW *win);
int get_str(void *vopt, WINDOW *win);
int trip_ch(int y, int x, int ch);

coord *find_dest(THING *tp);
coord *rndmove(THING *who);

THING *find_obj(int y, int x);
THING *get_item(char *purpose, int type);
THING *leave_pack(THING *obj, bool newobj, bool all);
THING *new_item();
THING *new_thing();

struct room *roomin(coord *cp);

static const int MAXDAEMONS = 20;

extern struct delayed_action {
  int d_type;
  void (*d_func)();
  int d_arg;
  int d_time;
} d_list[MAXDAEMONS];

typedef struct {
  char *st_name;
  int st_value;
} STONE;

extern int total;
extern int between;
extern int group;
extern coord nh;
extern char *rainbow[];
extern int cNCOLORS;
extern STONE stones[];
extern int cNSTONES;
extern char *wood[];
extern int cNWOOD;
extern char *metal[];
extern int cNMETAL;
