#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "西城门");
        set("long", @LONG
这里是京城的西城门，厚实坚固的古城墙高高耸立着。城门两旁
整齐的站着几个卫兵，仔细的监守着这里。每天都有许多人经过这里
出入京城。出了西城门，一条笔直的大官道向东西两边延伸。西边的
官道上人来车往，尘土飞扬。东方则是通往京城的西单北大街。
LONG );
        set("exits", ([
                "east" : "/d/beijing/ximenkou",
                "west" : "/d/beijing/ximenwai",
        ]));
        set("objects", ([
                "/d/beijing/npc/ducha" : 1,
                "/d/beijing/npc/bing1" : 2,
                "/d/beijing/npc/tangzi" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2850);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}