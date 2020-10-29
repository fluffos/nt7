#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "大道");
        set("long", @LONG
这里是紫禁城北边靠近城门的一条宽阔的大道，南方不远就是京
城的永定门了，厚实坚固的古城墙高高耸立着。每天都有许多人经过
这条大道出入京城。北方则经过天坛通往京城的中心。东面则是无极
帮的北京分舵。
LONG );
        set("exits", ([
                "north" : "/d/beijing/tiantan",
                "south" : "/d/beijing/yongdingmen",
        "east" : "/d/beijing/wjb_bjwfb",
        ]));
        set("objects", ([
                "/d/beijing/npc/tiaofu" : 1,
                "/d/beijing/npc/kid1" : 1,
                "/d/beijing/npc/tangzi" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7620);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}