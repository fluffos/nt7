// Room: /d/quanzhou/xinmenji.c
// Last Modified by Lonely on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "新门集");
        set("long", @LONG
这是泉州南面东西向的一条干道，规模不大。南边有家茶居，西边
是新门吊桥，东边则是市集。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"taoranju",
                "south" : __DIR__"taocipu",
                "east"  : __DIR__"jishi",
                "west"  : __DIR__"diaoqiao",
        ]));
	set("coor/x", -910);
	set("coor/y", -7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}