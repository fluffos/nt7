// Room: /d/city/jiaowai3.c
// Jan. 8.1998 by Venus
#include <room.h>
inherit ROOM;

void create()
{
    set("short", "树林");
        set("long", @LONG
扬州郊外的树林，松枝挺拔，乔木横斜。林间小道，逶迤随远。
林中蝉鸣厮闹，鸟啼宛转，使你顿时烦意尽消。    地上落了很多树
枝石块。
LONG );
    set("exits", ([
        "north" : "/d/city/jiaowai2",
        "south" : "/d/city/jiaowai4",
    ]));
    set("objects", ([
        "/d/city/obj/shitou": 2,
    ]));
//    set("no_clean_up", 0);
    set("outdoors", "yangzhou");
	set("coor/x", 40);
	set("coor/y", -30);
	set("coor/z", 0);
	setup();
    replace_program(ROOM);
}