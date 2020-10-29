#include <room.h>
inherit ROOM;

void create()
{
        set("short", "鳌府走廊");
        set("long", @LONG
一条木制结构的走廊，地面被打整得一尘不染，很是光滑。鳌府
的丫鬟和下人穿梭至其中。西边是鳌狠的书房，东边是鳌狠府的后院。
LONG );

        set("exits", ([
                "east" : "/d/beijing/aofu_houyuan",
                "west" : "/d/beijing/aofu_shufang",
        ]));
        set("objects", ([
                "/d/beijing/npc/jiading_a" : 1,
                "/d/beijing/npc/yahuan_a" : 1,
        ]));
	set("coor/x", -2830);
	set("coor/y", 7790);
	set("coor/z", 0);
	setup();
}