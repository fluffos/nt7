#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "城门口");
        set("long", @LONG
这里是京城西城城边靠近城门的一条宽阔的大道，西方就是京城
的西城门了，厚实坚固的古城墙高高耸立着。每天都有许多人经过这
条大道出入京城。东方是京城的西单北大街。
LONG );
        set("exits", ([
                "west" : "/d/beijing/xichengmen",
                "east" : "/d/beijing/bei_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/tiaofu" : 1,
                "/d/beijing/npc/old2" : 1,
                "/d/beijing/npc/tangzi" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}