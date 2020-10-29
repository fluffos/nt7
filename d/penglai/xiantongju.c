inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "仙童居");
        set("long",@LONG
对于仙童相信大家已经很熟悉了，仙童在此恭候多时了。
这里可以进行仓库物品的存取。但见四周金光闪耀，仙气缭
绕，似乎要比扬州仓库增色不少。
LONG);

        set("exits", ([
                "southwest"    : __DIR__"caiyunjian2",        
                "northeast"    : __DIR__"changshengmeilin1",                
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛
        set("no_fight", 1);

        set("objects", ([
                "/d/city/npc/xiantong" : 1,
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
}
