// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <room.h>
inherit ROOM; 


void create()
{
        set("short", "起点"); 
        set("long", HIG "这是一个待建的房间。\n" NOR);

        set("exits", ([ /* sizeof() == 1 */
                "east" : "/data/room/redl/dadian",
        ]));

        set("no_rideto", 1);
        set("no_flyto", 1);
        setup();
}



