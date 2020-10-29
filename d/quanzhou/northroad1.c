// Room: /d/quanzhou/northroad1.c
// Last Modified by Lonely on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "刺桐北路");
        set("long", @LONG
这是泉州的主要干道，笔直宽阔，车水马龙，热闹非凡。南面是热
闹喧哗的中心广场，嘈杂的声音远远便能听到。东边有家鸿福楼。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([ 
                "east"  : __DIR__"kedian",
                "south" : __DIR__"guangchang",
                "north" : __DIR__"northroad2",
        ]));
	set("coor/x", -900);
	set("coor/y", -7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}