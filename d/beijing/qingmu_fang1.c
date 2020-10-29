#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青木堂");
        set("long", @LONG
这里是一间看似很普通的民居，不过却要比通常的民居大了数倍。
房间中坐着一个干瘦老头。房间的南边又是一道门。
LONG );
       set("exits", ([
                "south" : "/d/beijing/qingmu_dating",
                "west" : "/d/beijing/qingmu_dayuan",
        ]));
        set("objects", ([
                "/d/beijing/npc/xutianchuan" : 1
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7620);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}