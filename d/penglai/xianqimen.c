inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "仙气门");
        set("long",@LONG
到了这里，四周尽是白茫茫的仙气，犹如置身在梦境之中，感
觉自己随着仙气缭缭升起，就快成了神仙。不远处隐约可见一块碑
石，上书「仙气门」三个大字。似乎岛上的雾气都是从这里涌出来
的。阵阵梵音又渐渐传来，似乎越来越近了。
LONG);

        set("exits", ([
                "west"   : __DIR__"zhulin2",
                "east"    : __DIR__"wuchi",
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
