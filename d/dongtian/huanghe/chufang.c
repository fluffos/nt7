// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 

void create()
{
        set("short", "厨房");
        set("long", 
"这是厨房，几个看起来就是凡人的小厮和健妇正在辛勤忙碌着。一阵饭\n"
"菜的清香飘过，使人食欲大振。\n"
);
                //set("outdoors", "dongtian");
                set("exits",([ /* sizeof() == 1 */
                        "south" : __DIR__"caidi",
                ]));

        set("objects", ([ 
                "/clone/fam/pill/water.c" : random(4) + 3,
                "/clone/fam/pill/food.c" : random(21) + 10,
                "/clone/fam/pill/food1.c" : random(3),
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




