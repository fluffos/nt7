// Room: /d/quanzhou/eastroad2.c
// Last Modified by Lonely on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "刺桐东路");
        set("long", @LONG
这是泉州的主要干道，笔直宽广，车水马龙，热闹非凡。恩怨巷坐
落在北边，可通至擂台。擂台比武可是城里的一大盛事。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "west"   : __DIR__"eastroad1",
                "north"  : __DIR__"enyuanxiang",
        ]));
	set("coor/x", -880);
	set("coor/y", -7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}