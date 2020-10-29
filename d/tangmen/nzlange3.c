//nzlange3.c                四川唐门—碎石小路

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "碎石小路");
        set("long",
"这是一条碎石铺就的小路。一些唐门的弟子往来穿梭，这里还真是很\n"
"热闹。这里向\n"
);
        set("exits", ([
                        "west"  : __DIR__"nzlange2",
                        "east"  : __DIR__"lianparry",
                        "north" : __DIR__"lianthrow",
                        "south" : __DIR__"liandodge",
        ]));
        set("area", "tangmen");
        set("outdoors", "tangmen");
        setup();
//        replace_program(ROOM);
}