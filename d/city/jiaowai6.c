// Room: /d/city/jiaowai6.c
// Jan. 8.1998 by Venus
#include <room.h>
inherit ROOM;

void create()
{
    set("short", "树林");
        set("long", @LONG
扬州郊外的树林，松枝挺拔，乔木横斜。林间小道，逶迤随远。
林中蝉鸣厮闹，鸟啼宛转，使你顿时烦意尽消。        地上落了很
多树枝石块。
LONG );

    set("exits", ([
        "east" : "/d/city/jiaowai5",
        "west" : "/d/city/jiaowai7",
    ]));
    set("objects", ([
        CLASS_D("gaibang")+"/kuai-huosan" : 1,
        "/d/city/obj/shitou": 2,
    ]));
//    set("no_clean_up", 0);
    set("outdoors", "yangzhou");
	set("coor/x", 20);
	set("coor/y", -40);
	set("coor/z", 0);
	setup();
    replace_program(ROOM);
}