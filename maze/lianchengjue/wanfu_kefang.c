
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIG + "万府客房" + NOR);
        set("long", "这里是荆州万府，乃万震山府邸，四处朱墙高瓦，好不气派。\n"); 
        
        set("no_bid", 1);
        set("no_magic", 1);
        set("no_rideto", 1);
        
        set("exits", ([ 
                "out" : "/d/city/wumiao", 
        ]));

        setup();
}

