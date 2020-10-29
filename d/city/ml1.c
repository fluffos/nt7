// Room: /city/milin.c

#include <room.h>
inherit BUNCH_ROOM;

void create()
{
	set("short", "青竹林");
        set("long", @LONG
这是一片茂密的青竹林，一走进来，你仿佛迷失了方向。
LONG );
	set("exits", ([
		"east" : "/d/city/ml2",
		"west" : __FILE__,
		"south" : "/d/city/dongmen",
		"north" : __FILE__,
	]));
	set("outdoors", "city");
	set("coor/x", 40);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
}