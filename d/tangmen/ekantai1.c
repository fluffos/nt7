//ekantai1.c  by Lonely

#include <room.h>

inherit ROOM;

void create()
{        
        set("short", "东较武场看台");
        set("long",
"这是唐门的东较武场看台。虽然对于看比武大赛来说，这里不是最佳\n"
"的位置，但是这里是喝彩声最响的地方。因为聚在这里的，通常是唐门的\n"
"晚辈弟子，最随便，最冲动，也最有激情。南面，是东较武场的中间看台。\n"
);        
        set("no_steal", "1");
        set("no_fight", "1");
        set("exits", ([
                "south" : __DIR__"ekantai2",
        ]));
        setup();
        replace_program(ROOM);
}