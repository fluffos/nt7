#include <room.h>
inherit ROOM;

void create()
{
        set("short", "韦府走廊");
        set("long", @LONG
这是一条木制的走廊，地面很是光滑，被打整得一尘不染。几个
韦府的下人在此走动。北边是个巨大的花园。
LONG );
       set("exits", ([
                "north" : "/d/beijing/weifu_dayuan",
                "east" : "/d/beijing/weifu_men",
        ]));
        set("objects", ([
                "/d/beijing/npc/shizhe" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}