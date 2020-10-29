inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "兰草地");
        set("long",@LONG
来到这里，兰草的香味已经令人心旷神怡，四周飘着淡淡的仙
气，兰草在仙气的笼罩下显得格外美丽。置身于如此境界，真可谓
夫复何求。
LONG);

        set("exits", ([
                "north"    : __DIR__"huixiandao",
                "south"    : __DIR__"tianxiandao1",        
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛

        if (random(3) == 1)
        {
                set("objects", ([
                        __DIR__"obj/lancao" : 3,
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
