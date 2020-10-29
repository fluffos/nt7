// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 

void create()
{
        set("short", "山路");
        set("long", 
"前面已然是山路崎岖，不知名发光的石头铺砌成弯弯曲折的小路，淡淡\n"
"的发出青色的光芒，整条路顺山而上，远远望去如一条青色大蛇蜿蜒扭转，\n"
"不知这山路尽头是何去处。\n"
);
                set("outdoors", "dongtian");
                set("exits",([ /* sizeof() == 1 */
                        "south" : __DIR__"zoulang24",
                        "east" : __DIR__"shanlu2",
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



