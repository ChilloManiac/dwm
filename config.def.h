/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int swallowfloating    = 0;
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 40;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 40;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "FiraCodeNerdFont:size=13"};
static const char dmenufont[]       = "FiraCodeNerdFont:size=13";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { " ", " ", " ", " ", "阮 ", " ", "ﭮ ", "聆 ", " " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance    title           tags mask     isfloating    isterminal  noswallow   monitor */
    {"Thunderbird",     NULL,       NULL,           1 << 8,         0,          0,          0,          -1},
    {"Slack",           NULL,       NULL,           1 << 7,         0,          0,          0,          -1},
    {"discord",         NULL,       NULL,           1 << 6,         0,          0,          0,          -1},
    {"Xfce4-terminal",  NULL,       NULL,           0,              0,          1,          -1,         -1},
    {"Steam",           NULL,       NULL,           1 << 5,         0,          0,          0,          -1},
    {"Spotify",         NULL,       NULL,           1 << 4,         0,          0,          0,          -1},
    {NULL,              NULL,       "gotop",        0,              1,          0,          -1,         -1},
    {NULL,              NULL,       "weather-tui",  0,              1,          0,          -1,         -1},
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "|||",      col },
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
/*  { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* My terminal */
#define termToUse "xfce4-terminal"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { termToUse, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,           {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,           {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,       {0} },
	{ MODKEY,                       XK_h,      setmfact,        {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,        {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,      incnmaster,     {.i = +1 } },
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_space,  zoom,            {0} },
	{ MODKEY,                       XK_Tab,    view,            {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,      {0} },
	{ MODKEY,                       XK_t,      setlayout,       {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,       {.v = &layouts[4]} },
	{ MODKEY,                       XK_y,      setlayout,       {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      setlayout,       {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_u,      setlayout,       {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating,  {0} },
	{ MODKEY,                       XK_0,      view,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,             {.ui = ~0 } },
	{ MODKEY,                       XK_o,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_p,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_p,      tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                       0)
	TAGKEYS(                        XK_2,                       1)
	TAGKEYS(                        XK_3,                       2)
	TAGKEYS(                        XK_4,                       3)
	TAGKEYS(                        XK_5,                       4)
	TAGKEYS(                        XK_6,                       5)
	TAGKEYS(                        XK_7,                       6)
	TAGKEYS(                        XK_8,                       7)
	TAGKEYS(                        XK_9,                       8)
    { MODKEY,                       XK_w,      spawn,           SHCMD("firefox")},
    { MODKEY,                       XK_c,      spawn,           SHCMD("code")},
    { MODKEY|ControlMask,           XK_l,      spawn,           SHCMD("dm-tool lock")},
    { MODKEY,                       XK_Down,   spawn,           SHCMD("cvolset.sh 0")},
    { MODKEY,                       XK_Up,     spawn,           SHCMD("cvolset.sh 1")},
    { MODKEY|ShiftMask,             XK_Down,   spawn,           SHCMD("cvolset.sh 2")},
    { MODKEY|ShiftMask,             XK_Up,     spawn,           SHCMD("cvolset.sh 3")},
    { MODKEY|ShiftMask,             XK_w,      spawn,           SHCMD("dmenuwalls")},
    { MODKEY,                       XK_g,      spawn,           SHCMD("game")},

    // Vanity Gaps
    { MODKEY,                       XK_comma,  incrgaps,        {.i = -5 } },
    { MODKEY,                       XK_period, incrgaps,        {.i = +5 } },
    { MODKEY|ShiftMask,             XK_comma,  incrigaps,       {.i = -5 } },
    { MODKEY|ShiftMask,             XK_period, incrigaps,       {.i = +5 } },
    { MODKEY|ControlMask,           XK_comma,  incrogaps,       {.i = -5 } },
    { MODKEY|ControlMask,           XK_period, incrogaps,       {.i = +5 } },
    { MODKEY,                       XK_minus,  defaultgaps,     {0} },
    { MODKEY|ShiftMask,             XK_minus,  togglegaps,      {0} },

    // Fullscreen
	{ MODKEY,                       XK_f,      togglefullscr,   {0} },

    //Sticky    
	{ MODKEY,                       XK_s,      togglesticky,    {0} },

    //Flameshot
    { MODKEY|ShiftMask,             XK_s,      spawn,           SHCMD("flameshot gui")},

    //xrdb
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

