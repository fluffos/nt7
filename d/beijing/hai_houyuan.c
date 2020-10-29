inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","后院");
        set("long", @LONG
这里是海澄公府大厅后侧的一个小花园，杂乱地种着各种花草，
看来无人打理，杂草已经长得很高了。一些鲜花夹杂在草丛中，阵阵
花香不断地飘过。
LONG );
        set("exits", ([
                "north" : "/d/beijing/hai_dating",
        ]));

	set("coor/x", -2810);
	set("coor/y", 7610);
	set("coor/z", 0);
	setup();
}