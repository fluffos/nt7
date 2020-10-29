//tangting.c                四川唐门—唐听卧室

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "寝室");
        set("long",
"这是一间简陋的卧室。屋中只有一张硬木床和一张枣木红桌。这里住\n"
"着唐老太太的贴身保镖唐听。\n"
);
        set("exits", ([
                        "west" : __DIR__"nzlang3",
        ]));
        set("area", "tangmen");
        set("objects", ([__DIR__"npc/tangting" : 1,]));
        setup();
        replace_program(ROOM);
}