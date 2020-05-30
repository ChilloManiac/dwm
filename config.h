/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 40;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 40;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "FontAwesome5FreeSolid:size=13","FiraCode:size=11"};
static const char dmenufont[]       = "FiraCode:size=12";
static const char col_bg[]          = "#282828";
static const char col_fg[]          = "#ebddd2";
static const char col_brd[]         = "#fe8019";
static const char col_bg_alt[]      = "#1d2021";
static const char col_fg_alt[]      = "#a89984";
static const char col_brd_alt[]     = "#000000";
static const char *colors[][3]      = {
	/*               fg             bg              border   */
	[SchemeNorm] = { col_fg,        col_bg,         col_brd_alt},
	[SchemeSel]  = { col_fg_alt,    col_bg_alt,     col_brd},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance      title       tags mask     isfloating   monitor */
  //{"firefox",     NULL,       NULL,       1 << 8,         0,          -1},
    {"Thunderbird", NULL,       NULL,       1 << 8,         0,          -1},
    {"Slack",       NULL,       NULL,       1 << 7,         0,          -1},
    {"discord",     NULL,       NULL,       1 << 6,         0,          -1},
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_fg_alt, "-sb", col_fg, "-sf", col_brd, NULL };
static const char *termcmd[]  = { termToUse, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,           {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,           {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,       {0} },
	{ MODKEY,                       XK_h,      setmfact,        {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,        {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_h,      incnmaster,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_l,      incnmaster,      {.i = -1 } },
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_space,  zoom,            {0} },
	{ MODKEY,                       XK_Tab,    view,            {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,      {0} },
	{ MODKEY,                       XK_t,      setlayout,       {.v = &layouts[0]} },
	{ MODKEY,                       XK_y,      setlayout,       {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      setlayout,       {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_u,      setlayout,       {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating,  {0} },
	{ MODKEY,                       XK_0,      view,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,             {.ui = ~0 } },
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
    { MODKEY|ControlMask,           XK_q,      spawn,           SHCMD("dm-tool lock")},
    { MODKEY,                       XK_c,      spawn,           SHCMD("code")},

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

