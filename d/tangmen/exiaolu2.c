//exiaolu2.c                四川唐门—碎石小路

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "碎石小路");
        set("long",
"这里是后山小路。道路越来越窄，杂草却更加茂密已经齐腰高矮不时\n"
"从远处传来声声怪啸，让人头皮发麻，小路弯弯曲曲的向前伸去通向更加\n"
"阴暗的后山。\n"
);
        set("exits", ([
                        "west" : __DIR__"exiaolu1",
                        "eastup" : __DIR__"houshan",
        ]));
        set("area", "tangmen");
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}