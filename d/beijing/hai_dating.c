inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","海澄公府大厅");
        set("long", @LONG
这是海澄公府的大厅，大厅不大，装饰也不华丽，很难想象这里
竟然是一等公爵的居所。此时大厅内外一片嘈杂，挤满了上门来寻事
的御前侍卫。
LONG );
        set("exits", ([
                "north" : "/d/beijing/hai_dayuan",
                "south" : "/d/beijing/hai_houyuan",
        ]));
        set("objects", ([
                "/d/beijing/npc/duolong" : 1,
                "/d/beijing/npc/zheng" : 1,
                "/d/beijing/npc/feng" : 1,
        ]));

	set("coor/x", -2810);
	set("coor/y", 7620);
	set("coor/z", 0);
	setup();
}