//tangltt.c                四川唐门—老太太卧室

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "卧室");
        set("long",
"这是唐门掌门唐老太太的卧室，很简单，没有什么特别。\n"
);
        set("exits", ([
                        "south" : __DIR__"nzlang3",
        ]));
        set("area", "tangmen");
        set("objects", ([
                CLASS_D("tangmen") + "/tangltt" : 1,
        ]));
        setup();
        replace_program(ROOM);
}