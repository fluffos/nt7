// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 


void create()
{
        set("short", "抱犊山道");
        set("long", 
"这是七十二福地中的抱犊山山道，北上有条幽静小路蜿蜒，两旁\n"
"全是火红色的枫叶林，只微微听得见流水潺潺的声音。\n"
);
                set("outdoors", "yangzhou");
                set("exits",([ /* sizeof() == 1 */
                        "northup" : __DIR__"baodu3",
                        "southdown" : __DIR__"baodu",
                ]));

        //set("no_dazuo",1);
        //set("no_kill",1);
        //set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
                //set("no_magic", 1); 
        set("no_sleep_room", 1); 
        set("no_get", 1);
        set("no_user_kill", 1);
//        set("max_carry_user" ,5);
//        set("max_carry_exit" ,"out");
        
        setup();
}




