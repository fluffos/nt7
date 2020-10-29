//exiaolu1.c                四川唐门—碎石小路

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "碎石小路");
        set("long",
"这里是后山小路。只容一人通过，两边杂草丛生，不时传出悉悉索索\n"
"的拨草声，偶尔还有一两只小动物自面前掠过，小路弯弯曲曲的向前伸去，\n"
"通向更加阴暗的后山。\n"
);
        set("exits", ([
                        "south" : __DIR__"chaifang",
                        "east" : __DIR__"exiaolu2",
        ]));
        set("area", "tangmen");
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}