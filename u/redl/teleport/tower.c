// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 

void create()
{
        set("short", "铁塔之顶");
        set("long", 
"这是开封铁塔尖尖的顶部，几个模糊的黑影正静静趴伏在塔的周\n"
"围各檐角上，紧张地窥视着塔里的情况。\n"
);
                set("outdoors", "yangzhou");
                set("exits",([ /* sizeof() == 1 */
                        "out" : __DIR__"teleport",
                ]));

        set("no_dazuo",1);
        set("no_kill",1);
        set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
                set("no_magic", 1); 
        set("no_sleep_room", 1); 
        set("max_carry_user" ,3);
        set("max_carry_exit" ,"out");
        
        setup();
}



