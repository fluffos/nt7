#include <room.h>
inherit ROOM;

void create()
{
        set("short", "天坛北门");
        set("long", @LONG
这里是天坛的北门，站在这里已经可以清楚的望见天坛中间那座
最高的建筑——皇穹宇，相传每当皇帝祭天之后，总是到那里向着无
数个神位叩头以致谢意。从天坛北门往北则通往著名的凡陛桥。
LONG );
        set("exits", ([
                "south" : "/d/beijing/tiantan",
                "north" : "/d/beijing/tianqiao",
        ]));
        set("objects", ([
                "/d/beijing/npc/girl2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7640);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}