// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 

void create()
{
        set("short", "传送阵");
        set("long", 
"这里是山巅的一片空地。空地正中，赫然是一座巨大的圆形法阵，底部\n"
"悬空，十三根白玉石所做的高达三丈的巨大石柱支撑起整座法阵。其中法阵\n"
"边缘共有十二根白玉石柱，每一根都有二人合抱之粗，而在法阵中间，最粗\n"
"大的一根白玉石柱看上去至少需要六七个人才能合抱过来，高入云霄。石柱\n"
"不时亮起，法阵之中隐隐有人影显现。\n"
);
                set("outdoors", "dongtian");
                set("exits",([ /* sizeof() == 1 */
                        "east" : __DIR__"houshan",
                        "enter" :"/u/redl/teleport/teleport",
                ]));

        set("no_fight",1);//这里绝对不能战斗，不然会回到水牢
        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
        set("no_drift", 1);
        set("no_sleep_room", 1); 
        //set("max_carry_user" ,20);
        
        setup();
}



