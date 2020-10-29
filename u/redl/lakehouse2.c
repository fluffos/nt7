// This program is a part of NITAN MudLIB 
// redl 2013/5
#include <ansi.h> 
#include <room.h> 
inherit ROOM; 

void create()
{
        set("short", "木屋内");
        set("long", 
"这是间看上去十分舒适的大屋子，室内古朴的家俱和恰当的陈设，显\n"
"出曾有人幸福生活过的痕迹。明亮的窗户外只见几片枯叶飞过，忽闻寒鸦\n"
"从屋顶外传来呱啊地一声惊叹。\n"
);
         set("exits",([ /* sizeof() == 1 */
                 "out" : __DIR__"lakehouse",
         ]));

        set("objects", ([
//                "/u/redl/obj/mbox" : 1,
        ]));

        set("sleep_room", 1);
        set("loving_room", 1);
        set("no_fight", 1);

                set("no_rideto", 1);
                set("no_flyto", 1);
        
        setup();
}

void init()
{
        object me = this_player();
        if ( query("id", me) != "redl" && query("couple/couple_id", me) != "redl" )
        {
                        message_vision(YEL "一股微风吹过，把$N吹到了室外。\n" NOR, me);
                        me->move(__DIR__"lakehouse");
                        return;
        }
}




