#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青木堂");
        set("long", @LONG
尚未开放。
LONG );
        set("exits", ([
                "north" : "/d/beijing/yangliu3",
        ]));
        replace_program(ROOM);
}
