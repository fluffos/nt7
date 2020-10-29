// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 

string look_bei(object me)
{
        string *owns;
        if (me->is_busy()) {
                return  NOR "你还是忙完手头上的事情再看吧。\n" NOR;
        }
        me->start_busy(3);
        owns = __DIR__"data.c"->do_load("owners");
        if (!undefinedp(owns) && arrayp(owns) && sizeof(owns)>0) {
                return CYN "石碑上刻着一行名字："+implode(owns, "、")+"。\n"+NOR+"( 记于 - "+ctime(__DIR__"data.c"->do_load("hold_time"))+" )\n\n" NOR;  
        }
        return CYN "石碑上空空如也。\n\n" NOR;  
}

void create()
{
        set("short", "前庭");
        set("long", 
"广场尽头，一座石桥，无座无墩，横空而起，一头搭在广场，径直斜伸\n"
"向上，入白云深处，如姣龙跃天，气势孤傲。阳光照下，整座桥散发七彩颜\n"
"色，如天际彩虹落凡间，绚丽缤纷，美轮美奂。踏上石桥，两侧流水潺潺，\n"
"清澈无比，走过石桥，竟是出了云海，眼前蓦然一亮，只见长空如洗，蓝的\n"
"如ＰＳ过一样。四面天空，广无边际。下有云海茫茫，一眼望去，心胸顿时\n"
"为之一宽。这便是前庭所在，庭中竖着一个石碑("CYN"bei"NOR")。\n"
NOR
);
                set("outdoors", "dongtian");
                set("exits",([ /* sizeof() == 1 */
                        "north" : __DIR__"dadian",
                        "south" : __DIR__"guangchang",
                        "east" : __DIR__"zoulang11",
                        "west" : __DIR__"zoulang21",
                ]));
        set("item_desc", ([
                "bei": (: look_bei :),
        ]) );

        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
        set("no_drift", 1);
        set("no_sleep_room", 1); 
        set("max_carry_user" ,20);
        
        setup();
}

void init()
{
        object me = this_player();
        if (userp(me)) me->command("maphere");
        ::init();
}

