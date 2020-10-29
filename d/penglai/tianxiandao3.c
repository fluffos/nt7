inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "天仙道");
        set("long",@LONG
走在这根道上犹如踏上云层的感觉一般，轻飘飘的，从未试过
这种感觉，阳光照射在仙气上折射出的各种光圈，五彩斑斓，美丽
非常。
LONG);

        set("exits", ([
                "west"     : __DIR__"tianxiandao2",
                "east"     : __DIR__"diexiandao",        
                "north"    : __DIR__"caiyunjian1",        
                "south"    : __DIR__"lancaodi2",                
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
