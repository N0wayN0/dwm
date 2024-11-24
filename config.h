/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=13:pixelsize=22" };
//static const char *fonts[]          = { "monospace:size=18" };
static const char dmenufont[]       = "monospace:size=13";
static const char col_gray1[]       = "#888888";  /* background of bar */
static const char col_gray2[]       = "#222222";  /* border of unfocused window */
static const char col_gray3[]       = "#000000";  /* text color on the bar */
static const char col_gray4[]       = "#000000";  /* focused tags and window titlt */
static const char col_cyan[]        = "#33a1b5";  /* border of focused window and bar */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "float",    NULL,       NULL,       0,            1,           -1 },
	{ NULL,       "floating", NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ ALTKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ ALTKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ ALTKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ ALTKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define CMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"
#include <X11/XF86keysym.h>

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[] = { "st", NULL };
static const char *floathtop[] = { "floating.sh", "htop", NULL };
static const char *floatvim[] = { "notepad.sh", NULL };
static const char *firefox[] = { "firefox", NULL };
static const char *killall[] = { "kill_all.sh", NULL };
static const char *youtube[] = { "/root/.local/bin/watch_YT_now", NULL };
//static const char *set20[] = { "amixer set Master 20% && kill -RTMIN+21 $(pidof dwmblocks)", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	/* WINDOW MANAGEMENT */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
 	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
 	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ ALTKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
	{ ALTKEY|ShiftMask,             XK_Tab,    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },

	/* LAYOUT MANAGEMENT */
	{ MODKEY|ControlMask,   		XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} }, /* tile */
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[0]} }, /* float */
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, /* mono */
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	/* MONITOR MANAGEMENT */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	
    /* TAGS MANAGEMENT */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

    /* PROGEAMS MANAGEMENT */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = firefox } },
	{ MODKEY,                       XK_a,      spawn,          {.v = youtube } },
	{ ALTKEY,                       XK_Return, spawn,          {.v = floatvim } },
	{ ALTKEY,                       XK_r,      spawn,          {.v = floathtop } },
	{ MODKEY,                       XK_equal,  spawn,          CMD("change_volume.sh up") },
	{ MODKEY,                       XK_minus,  spawn,          CMD("change_volume.sh down") },
	{ ALTKEY|ShiftMask,             XK_q,      quit,           {0} },
    { ALTKEY|MODKEY|ControlMask,    XK_End,    spawn,          {.v = killall} }, 

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button4,        cyclelayout,    {.i = +1 } }, // mouse wheel up
	{ ClkLtSymbol,          0,              Button5,        cyclelayout,    {.i = -1 } }, // mouse wheel down
	{ ClkWinTitle,          0,              Button1,        zoom,           {0} },
	{ ClkWinTitle,          0,              Button3,        killclient,     {0} },
	{ ClkWinTitle,          0,              Button4,        focusstack,     {.i = +1 } },
	{ ClkWinTitle,          0,              Button5,        focusstack,     {.i = -1 } },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} }, // left mouse button
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} }, // middle mouse button
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} }, // right mouse button
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} }, // mouse wheel up
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} }, // mouse wheel down
    { ClkStatusText,        ShiftMask,      Button1,        sigstatusbar,   {.i = 6} },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            0,              Button2,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

