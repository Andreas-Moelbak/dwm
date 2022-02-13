/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 5;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "FiraCode Nerd Font:size=10", "Font Awesome 5 Free:pixelsize=10:antialias=true:autohint=true"  };
static char normbgcolor[]           = "#2b2d3a";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#e2e2e3";
static char selfgcolor[]            = "#e2e2e3";
static char selbordercolor[]        = "#f39660";
static char selbgcolor[]            = "#474a5a";

static const char *colors[][3]      = {
	/*      			   fg           bg           border   */
       [SchemeNorm] =    { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  =    { selfgcolor,  selbgcolor,  selbordercolor  },
	   //[SchemeSel]  =	 { col_gray4, col_cyan,   col_cyan },
	   //[SchemeWarn] =	 { col_black, col_yellow, col_red },
	   //[SchemeUrgent]=	 { col_white, col_red,    col_red },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", "-e", "tmux"   , NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-g", "110x34", "-e", "python3", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask    isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,          NULL,       0,              1,          0,           0,        -1 },
	{ "Firefox", NULL,          NULL,       1 << 8,         0,          0,          -1,        -1 },
	{ NULL,	     "spterm",		NULL,		SPTAG(0),		1,			1,           0,        -1 },
	{ NULL,	     "spcalc",		NULL,		SPTAG(1),		1,			1,           0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "---",      horizgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_v,     ACTION##stack, {.i = 0 } }, \
	// { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	// { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	// { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	// { MOD, XK_x,     ACTION##stack, {.i = -1 } }, 

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },

	{ MODKEY,                       XK_BackSpace,	    spawn, SHCMD("sysact") },
	{ MODKEY|ShiftMask,             XK_BackSpace,	    spawn, SHCMD("sysact") },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	//{ MODKEY|ShiftMask,             XK_Tab,      setcfact,       {.f = +0.25} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          SHCMD("sysact") },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("$BROWSER") },
	//{ MODKEY|ShiftMask,             XK_w,      setcfact,       {.f = +0.25} },
	{ MODKEY,                       XK_e,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_e,      setcfact,       {.f = +0.25} },
	{ MODKEY,                       XK_r,      spawn,          SHCMD("st -e ranger") },
	{ MODKEY|ShiftMask,             XK_r,      spawn,          SHCMD("pcmanfm") },

    //Layouts
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_i,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ShiftMask,             XK_i,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1} },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1} },
    
	//{ MODKEY,                       XK_p,      setmfact,       {.f = +0.05} },
	//{ MODKEY|ShiftMask,             XK_p,      setcfact,       {.f = +0.25} },
	{ MODKEY,                       XK_a,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_a,      defaultgaps,    {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	//{ MODKEY|ShiftMask,             XK_s,      setcfact,       {.f = +0.25} },
	//{ MODKEY,                       XK_d,      spawn,          SHCMD("dmenu_run") },
	{ MODKEY,                       XK_d,      spawn,          SHCMD("rofi -show drun") },
	//{ MODKEY|ShiftMask,             XK_d,      setcfact,       {.f = +0.25} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[8]} },
	//{ MODKEY,                       XK_g,      setmfact,       {.f = +0.05} },
	//{ MODKEY|ShiftMask,             XK_g,      setcfact,       {.f = +0.25} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	//{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	//{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd} },
	{ MODKEY,                       XK_apostrophe,	    togglescratch,	    {.ui = 1} },
	{ MODKEY|ShiftMask,             XK_Return, togglescratch,  {.ui = 0} },
	{ MODKEY,                       XK_z,      incrgaps,       {.i = +3} },
	//{ MODKEY|ShiftMask,             XK_z,      incrgaps,       {.i = -3} },
	{ MODKEY,                       XK_x,      incrgaps,       {.i = -3} },
	//{ MODKEY|ShiftMask,             XK_x,      setcfact,       {.f = +0.25} },
	//{ MODKEY,                       XK_c,      setmfact,       {.f = +0.05} },
	//{ MODKEY|ShiftMask,             XK_c,      setcfact,       {.f = +0.25} },
	//{ MODKEY,                       XK_v,      setmfact,       {.f = +0.05} },
	//{ MODKEY|ShiftMask,             XK_v,      setcfact,       {.f = +0.25} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	//{ MODKEY|ShiftMask,             XK_b,      setcfact,       {.f = +0.25} },
	//{ MODKEY,                       XK_n,      setmfact,       {.f = +0.05} },
	//{ MODKEY|ShiftMask,             XK_n,      setcfact,       {.f = +0.25} },
	//{ MODKEY,                       XK_m,      setmfact,       {.f = +0.05} },
	//{ MODKEY|ShiftMask,             XK_m,      setcfact,       {.f = +0.25} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1} },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1} },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1} },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1} },

	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	//{ MODKEY,                       XK_Left,      setmfact,       {.f = +0.05} },
	//{ MODKEY|ShiftMask,             XK_Left,      setcfact,       {.f = +0.25} },
	//{ MODKEY,                       XK_Right,      setmfact,       {.f = +0.05} },
	//{ MODKEY|ShiftMask,             XK_Right,      setcfact,       {.f = +0.25} },
	//{ MODKEY,                       XK_Up,      setmfact,       {.f = +0.05} },
	//{ MODKEY|ShiftMask,             XK_Up,      setcfact,       {.f = +0.25} },
	//{ MODKEY,                       XK_Down,      setmfact,       {.f = +0.05} },
	//{ MODKEY|ShiftMask,             XK_Down,      setcfact,       {.f = +0.25} },

	//{ MODKEY,                       XK_Page_Up,      setmfact,       {.f = +0.05} },
	//{ MODKEY|ShiftMask,             XK_Page_Up,      setcfact,       {.f = +0.25} },
	//{ MODKEY,                       XK_Page_Down,      setmfact,       {.f = +0.05} },
	//{ MODKEY|ShiftMask,             XK_Page_Down,      setcfact,       {.f = +0.25} },


	//{ MODKEY,                       XK_F1,      spawn,     {.i = +1 } },
	//{ MODKEY,                       XK_F2,      spawn,     {.i = +1 } },
	//{ MODKEY,                       XK_F3,      spawn,     {.i = +1 } },
	//{ MODKEY,                       XK_F4,      spawn,     {.i = +1 } },
	//{ MODKEY,                       XK_F5,      spawn,     {.i = +1 } },
	//{ MODKEY,                       XK_F6,      spawn,     {.i = +1 } },
	//{ MODKEY,                       XK_F7,      spawn,     {.i = +1 } },
	//{ MODKEY,                       XK_F8,      spawn,     {.i = +1 } },
	//{ MODKEY,                       XK_F9,      spawn,     {.i = +1 } },
	//{ MODKEY,                       XK_F10,     spawn,     {.i = +1 } },
	//{ MODKEY,                       XK_F11,     spawn,     {.i = +1 } },
	//{ MODKEY,                       XK_F12,     spawn,     {.i = +1 } },

	{ 0, XF86XK_AudioMute,  		spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioMicMute,   	spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_PowerOff,	    	spawn,		SHCMD("sysact") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 5") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 5") },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
    #ifndef __OpenBSD__
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,	    	MODKEY,	    	Button4,        incrgaps,       {.i = +1} },
	{ ClkClientWin,	    	MODKEY,	    	Button5,        incrgaps,       {.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	//{ ClkTagBar,	    	0,	        	Button4,        shiftview,      {.i = -1} },
	//{ ClkTagBar,	    	0,              Button5,        shiftview,      {.i = 1} },
	{ ClkRootWin,	    	0,              Button2,        togglebar,      {0} },

};

