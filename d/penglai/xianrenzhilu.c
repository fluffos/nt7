inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "仙人指路");
        set("long",@LONG
这是通往蓬莱岛南山的必经之路，传说南山乃仙人修炼仙法的
地方，属于禁地。虽无人看守，但若没有仙人的指引外人是无论如
何也无法进入的。四周植物葱郁，仙气围绕，景致甚是迷人。不知
什么时候，在你面前已站着一位白衣仙人。
LONG);

        set("exits", ([
                "north"    : __DIR__"nanshandao2",
                "south"    : __DIR__"nanshanjiaoxia",
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛
        set("no_fight", 1);
        
        set("objects", ([
                __DIR__"npc/shouluxian" : 1,
        ]));
        
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
        
        tell_object(this_player(), HIG "\n说来奇怪，到了这里你突然闻到一阵酒香。\n" NOR);
}
