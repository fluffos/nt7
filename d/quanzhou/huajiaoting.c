// Room: /d/quanzhou/huajiaoting.c
// Last Modified by Lonely on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "花桥亭");
        set("long", @LONG
这是一个建在大路中央的小亭子，三三两两的行人在此休息。南去
便是顺济桥，可通往港口。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"shunjiqiao",
                "north" : __DIR__"jishi",
        ]));
	set("coor/x", -900);
	set("coor/y", -7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}