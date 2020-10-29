#include <room.h>
inherit ROOM;

void create()
{
        set("short", "鳌府走廊");
        set("long", @LONG
一条木制结构的走廊，地面被打整得一尘不染，很是光滑。鳌府
的丫鬟和下人穿梭至其中。南边是鳌府的大厅，北边则通往鳌府的后
院。
LONG );

        set("exits", ([
                "north" : "/d/beijing/aofu_houyuan",
                "south" : "/d/beijing/aofu_dating",
        ]));
        set("objects", ([
                "/d/beijing/npc/jiading_a" : 1,
        ]));
	set("coor/x", -2820);
	set("coor/y", 7780);
	set("coor/z", 0);
	setup();
}