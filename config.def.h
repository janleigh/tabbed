/* See LICENSE file for copyright and license details. */

/* appearance */
static char font[] = "Sarasa Mono CL Nerd Font:style=Regular:pixelsize=13";
static char *normbgcolor = "#131718";
static char *normfgcolor = "#b7b8b8";
static char *selbgcolor = "#101415";
static char *selfgcolor = "#c5c8c9";
static char *urgbgcolor = "#192022";
static char *urgfgcolor = "#f65b5b";
static char before[] = "";
static char after[] = "";
static char titletrim[] = "...";
static int tabwidth = 200;
static Bool foreground = True;
static Bool urgentswitch = False;
static int barheight = 40;

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
        { "font",         STRING,   &font },
        { "normbgcolor",  STRING,   &normbgcolor },
        { "normfgcolor",  STRING,   &normfgcolor },
        { "selfgcolor",   STRING,   &selfgcolor },
        { "selbgcolor",   STRING,   &selbgcolor },
        { "urgbgcolor",   STRING,   &urgbgcolor },
        { "urgfgcolor",   STRING,   &urgfgcolor },
        { "before",       STRING,   &before },
        { "after",        STRING,   &after },
        { "titletrim",    STRING,   &titletrim },
        { "tabwidth",     INTEGER,  &tabwidth },
};


/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int newposition = 0;
static Bool npisrelative = False;

#define SETPROP(p) { \
    .v = (char *[]){ "/bin/sh", "-c",                                       \
        "prop=\"`xwininfo -children -id $1 | grep '^     0x' |"             \
        "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |"      \
        "xargs -0 printf %b | dmenu -l 10 -w $1`\" &&"                      \
        "xprop -id $1 -f $0 8s -set $0 \"$prop\"",                          \
        p, winid, NULL                                                      \
    }                                                                       \
}

#define MODKEY ControlMask
static Key keys[] = {
    {MODKEY | ShiftMask, XK_Return, focusonce, {0}},
    {MODKEY | ShiftMask, XK_Return, spawn, {0}},

    {MODKEY | ShiftMask, XK_l, rotate, {.i = +1}},
    {MODKEY | ShiftMask, XK_h, rotate, {.i = -1}},
    {MODKEY | ShiftMask, XK_j, movetab, {.i = -1}},
    {MODKEY | ShiftMask, XK_k, movetab, {.i = +1}},
    {MODKEY, XK_Tab, rotate, {.i = 0}},

    {MODKEY, XK_grave, spawn, SETPROP("_TABBED_SELECT_TAB")},
    {MODKEY, XK_1, move, {.i = 0}},
    {MODKEY, XK_2, move, {.i = 1}},
    {MODKEY, XK_3, move, {.i = 2}},
    {MODKEY, XK_4, move, {.i = 3}},
    {MODKEY, XK_5, move, {.i = 4}},
    {MODKEY, XK_6, move, {.i = 5}},
    {MODKEY, XK_7, move, {.i = 6}},
    {MODKEY, XK_8, move, {.i = 7}},
    {MODKEY, XK_9, move, {.i = 8}},
    {MODKEY, XK_0, move, {.i = 9}},

    {MODKEY, XK_q, killclient, {0}},

    {MODKEY, XK_u, focusurgent, {0}},
    {MODKEY | ShiftMask, XK_u, toggle, {.v = (void *)&urgentswitch}},

    {0, XK_F11, fullscreen, {0}},
};