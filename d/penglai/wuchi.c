inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "雾池");
        set("long",@LONG
这岛上的仙气的源头竟是这雾池，但见池中不断涌出白色的雾
气，然后这些雾气吸收了岛上的灵气化为仙气向四周弥漫。看着阵
阵仙气飘起，你禁不住想吸（xi）上一口。
LONG);

        set("exits", ([
                "west"   : __DIR__"xianqimen",
                "east"   : __DIR__"tianxiandao1",
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

int do_xi()
{
        object me = this_player();
        
        if( !query("penglai/wuchi_quest/ok", me) )
        {
                message_vision(HIM "$N" HIM "深深地吸了一口雾池中的仙气 ……\n" NOR, me);
                tell_object(me, HIG "恭喜你，你的灵慧增加了。\n" NOR);
                set("penglai/wuchi_quest/ok", 1, me);
                addn("magic_points", 5000, me);
                me->save();
                return 1;
        }
        tell_object(me, HIC "你吸了一口池中仙气，觉得舒泰无比。\n" NOR);
        return 1;
}
