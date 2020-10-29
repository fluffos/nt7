
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIG + "小茅屋" + NOR);
        set("long", "这里是湘南农村的一处农家小院，一个简陋的茅屋前摆放着一个石桌。\n");
        
        set("no_bid", 1);
        set("no_magic", 1);
        set("no_rideto", 1);
        
        set("objects", ([
                __DIR__"npc/qichangfa" : 1,
                __DIR__"npc/qifang"    : 1,
        ]));
        
        set("exits", ([ 
                "out" : "/d/city/wumiao", 
        ]));
             
        set("no_get", "!@#$!@#%%^@!^\n");

        setup();
}

