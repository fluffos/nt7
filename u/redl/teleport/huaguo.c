// This program is a part of NITAN MudLIB  
// redl 2014/8
#include <ansi.h>  
#include <room.h>  
inherit "/u/redl/teleport/normal.c";  

void create()
{
        set("short","水帘洞");
        set("long", @LONG
宽阔的瀑布冲贯掩盖着洞门，内里一个大石窟。虚窗静室，滑凳
板生花。乳窟龙珠倚挂，萦回满地奇葩。锅灶傍崖存火迹，石座石床
真可爱，石盆石碗更堪夸。又见那一竿两竿修竹，三点五点梅花。正
当中有一石碣。碣上楷书大字镌着“花果山福地，水帘洞洞天”。        
LONG );
        set("outdoors", "yangzhou");
        set("exits",([ /* sizeof() == 1 */
            "out"  : "/u/redl/teleport/teleport",
        ]));

        set("no_rideto", 1);
        set("no_flyto", 1);
        set("no_protect", 1); 
        set("no_fly", 1);
        set("no_sleep_room", 1); 
        set("no_magic", 1); 

        set("no_user_yanjiu",1);
        set("no_user_kill", 1); 
        set("max_carry_user" ,99);
        set("max_carry_exit" ,"out");

        setup();
}

int valid_leave(object me, string dir)
{
        if (!interactive(me) || !playerp(me)) return 0;
        return ::valid_leave(me, dir);
}
