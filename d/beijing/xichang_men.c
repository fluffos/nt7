inherit ROOM;
#include <ansi.h>

void create()
{
        set("short",RED"西厂大门"NOR);
        set("long", @LONG
这里就是京城的特务机构——西厂的大门。这里警备深严，不时
有穿着制服的西厂官兵进进出出，望大门里望去，可以望见大门里面
有许多太监。大门两旁的西厂官兵正如狼似虎的盯着你看，如果你不
想找死的话，最好还是赶快离开的好。[2；37；0m
LONG );
        set("exits", ([
                "south" : "/d/beijing/xichang",
                "north" : "/d/beijing/di_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing3" : 2,
                "/d/beijing/npc/taijian" : 1,
        ]));
        set("no_fight", 0);
	set("coor/x", -2810);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (objectp(present("guan bing", environment(me))) && dir == "south")
                return notify_fail("西厂官兵伸手将你拦住。\n\n");
        return ::valid_leave(me, dir);
}