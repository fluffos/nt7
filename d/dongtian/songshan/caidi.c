// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 

void create()
{
        set("short", "菜地");
        set("long", 
"这里是菜地，土地被开垦地肥沃而且井然有序，青葱的菜蔬遍栽，许多\n"
"傀儡农民正在耕作，并不时把菜蔬收割传递到北面的厨房去。\n"
);
                set("outdoors", "dongtian");
                set("exits",([ /* sizeof() == 1 */
                        "east" : __DIR__"zoulang15",
                        "north" : __DIR__"chufang",
                        "west" : __DIR__"yaopu",
                ]));

        set("objects", ([ 
                (!random(4) ? "/u/redl/obj/chutou2" : "/u/redl/obj/chutou") : (!random(3) ? 2 : 1),
        ])); 

        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
        set("no_drift", 1);
        set("no_sleep_room", 1); 
        set("max_carry_user" ,3);
        
        setup();
}




