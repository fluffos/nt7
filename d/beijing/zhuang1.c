#include <room.h>
inherit BUNCH_ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
你走在一条小路上。前面道路崎岖，行人很少。西面有一条蜿蜒
的小岔路上山。
LONG );
        set("exits", ([
                "southwest" : "/d/beijing/road1",
                "north"     : "/d/beijing/zhuang2",
                "westup"    : "/d/beijing/shanlu1",
        ]));
        set("objects", ([
                "/d/taishan/npc/seng-ren" : 1,
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2780);
	set("coor/y", 7620);
	set("coor/z", 0);
	setup();
}
