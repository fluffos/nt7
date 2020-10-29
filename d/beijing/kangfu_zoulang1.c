#include <room.h>
inherit ROOM;

void create()
{
        set("short", "康府走廊");
        set("long", @LONG
这是一条木制的走廊，地面很是光滑，被打整得一尘不染。几个
康府的下人在此走动。南边是康府的大院，北边则是康府的大厅了。
LONG );
       set("exits", ([
                "north" : "/d/beijing/kangfu_dating",
                "south" : "/d/beijing/kangfu_dayuan",
        ]));
        set("objects", ([
                "/d/beijing/npc/jiading_k" : 1,
                "/d/beijing/npc/shizhe" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}