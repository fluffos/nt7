inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "梦幻琉璃");
        set("long",@LONG
这是一条用各种颜色的琉璃铺成的路，琉璃的光彩透仙气折射
出各种不同的色彩，照耀着整条道路，显得犹如梦境般奇幻。令人
匪夷所思。
LONG);

        set("exits", ([
                "north"    : __DIR__"tianxiandao1",
                "south"    : __DIR__"nanshandao1",        
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛

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
