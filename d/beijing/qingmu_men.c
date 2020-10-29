#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青木堂大门");
        set("long", @LONG
这是一个很普通的四合院，破旧的大门敞开着，大门里是一个大
院，院子四周是几间普通的民居。
LONG );
       set("exits", ([
                "north" : "/d/beijing/yangliu3",
                "south" : "/d/beijing/qingmu_dayuan",
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7630);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}