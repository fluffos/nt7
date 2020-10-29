#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "巫峡");
        set("long", @LONG
这里是长江三峡中的巫峡，也是最大最美的一个峡谷，神女峰高
高的耸立在江边，远远看去，由如一为亭亭玉立的少女，两岸风景美
不胜收。
LONG );
        set("exits", ([
                "east" :  __DIR__"sanxia1",
                "west" : __DIR__"sanxia3",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -15050);
	set("coor/y", -1830);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}