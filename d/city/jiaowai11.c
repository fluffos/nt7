// Room: /d/city/jiaowai11.c
// Jan. 8.1998 by Venus
#include <room.h>
inherit ROOM;

void create()
{
    set("short", "密林");
        set("long", @LONG
扬州郊外的茂密树林，阴森可怖。抬头不见天日。这里也是扬州
命案发生最多的地方。鸟兽蛇虫游荡不穷。
LONG );
    set("exits", ([
        "east"   : "/d/city/jiaowai10",
        "north"  : "/d/city/jiaowai13",
    ]));
    set("objects", ([
        "/clone/beast/dushe" : 2,
        "/d/city/obj/shitou": 1,
    ]));
//    set("no_clean_up", 0);
	set("coor/x", -40);
	set("coor/y", -30);
	set("coor/z", 0);
	setup();
    replace_program(ROOM);
}