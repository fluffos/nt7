//ycailiao.c                四川唐门—储料房

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "储料房");
        set("long",
"这里是唐门储存制造药物材料的房间。唐门暗器天下无双，除了暗器\n"
"手法之外，这里配制各种药物的材料，是功不可没。从这里取走的，是普\n"
"通的药物材料，当这些材料走出唐门的时候，都会令人心惊胆寒。东北边\n"
"是一条青石小路。\n"
);
        set("exits", ([
                        "northeast" : __DIR__"houroad2",
        ]));
        set("objects", ([
                __DIR__"npc/yjiading" : 1,
        ]));
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}