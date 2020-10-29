//shandao1.c                四川唐门—后山山道

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "山道");
        set("long",
"这里是通向山顶的小道。奇陡无比，一不小心就会摔下去，两边是高\n"
"耸入云的参天大树，林中传来野兽的撕咬声，令人毛骨悚然、不寒而立，\n"
"你全神贯注生怕有野兽扑来。\n"
);
        set("exits", ([
                        "westdown" : __DIR__"houshan",
                        "northeast" : __DIR__"shandao2",
        ]));
        set("area", "tangmen");
        set("objects", ([
                __DIR__"npc/xiezi" : 1,
                __DIR__"npc/snake" : 1,
        ]));
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}