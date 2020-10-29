//By rama@lxtx

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{ 
        set("short", HIG"树林"NOR);
        set("long", @LONG
忽然景色一转，前面变成了一片幽深的树林。你看看了看四周，
觉得周围有些地方不太对头，但是却说上不上来。树林里面似乎有些
声音传来。到底要不要进去呢？你不由踌躇起来。
LONG );
        set("outdoors", "yangzhou");
        set("exits", ([
                "east" :  "/d/city/dujiangqiao",
                "north" : "/d/city/shulin",
        ])); 
        set("objects", ([   
             "/d/city/npc/xdh-guard" : 2,   
            ]));
               
	set("coor/x", -10);
	set("coor/y", -40);
	set("coor/z", 0);
	setup();            
}

int valid_leave(object me, string dir)
{
    if (! userp(me) && objectp(present("shou wei", environment(me))) && dir == "north")
        return notify_fail("NPC不进去。\n");
    return ::valid_leave(me, dir);
}