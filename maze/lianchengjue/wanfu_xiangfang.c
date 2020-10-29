
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIG + "万府厢房" + NOR);
        set("long", "这里是万府西面的厢房，床上睡着一个女子，周围站满了万府的弟子和家丁。\n"); 
        
        set("no_bid", 1);
        set("no_magic", 1);
        set("no_rideto", 1);
        
        set("objects", ([
                __DIR__"npc/qifang" : 1,
        ]));

        set("exits", ([ 
                "out" : "/d/city/wumiao", 
        ]));

        setup();
}

