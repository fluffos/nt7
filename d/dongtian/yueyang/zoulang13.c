// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 

void create()
{
        set("short", "走廊");
        set("long", 
"这条长廊优雅精致，盘龙小柱顶着一个个的盖子，连接着各个去处，一\n"
"个个的盖子上面都是一幅精美的画卷，从盘古开天，到封神之战，让人走在\n"
"这长廊之上，也能感受上古之战的地裂天崩。\n"
);
                set("outdoors", "dongtian");
                set("exits",([ /* sizeof() == 1 */
                        "south" : __DIR__"zoulang12",
                        "north" : __DIR__"zoulang14",
                ]));

        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
        set("no_drift", 1);
        set("no_sleep_room", 1); 
        set("max_carry_user" ,20);
        
        setup();
}



