inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "竹林");
        set("long",@LONG
这是蓬莱仙岛中的竹林，四周雾气茫茫，梵音了了，真乃仙境。
不知这里的仙气是从何而来，竟觉得越来越多。
LONG);

        set("exits", ([
                "north"   : __DIR__"zhulin1",
                "east"    : __DIR__"xianqimen",
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛

        if (random(2) == 1)
        {
                set("objects", ([
                        __DIR__"obj/zhuye" : 1 + random(4),
                ]));
        }
        
        set("region", "penglai");
        setup();
}

void init ()
{
        if( !query_temp("apply/xianshu-lingwei", this_player()) )
        {
                if( !query("penglai/go_quest/ok", this_player()) )
                {
                        this_player()->start_busy(3);
                        tell_object(this_player(), NOR + WHT "你到了此处，四周仙气缭绕令你一时间难以辨别方向。\n" NOR);
                }
                else
                {
                        if (random(2))
                        {
                                this_player()->start_busy(1);
                                tell_object(this_player(), NOR + WHT "你到了此处，四周仙气缭绕令你一时间难以辨别方向。\n" NOR);                
                        }
                }
        }
}
