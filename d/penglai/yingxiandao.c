inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "迎仙道");
        set("long",@LONG
仙者在出岛时法力会受到彩石沙滩的影响而减弱，当再次回到
岛上后需要在距离这里不远处的修真池中进行修炼以帮助恢复法力。
此路便是为迎接从修真池中修炼出来的仙者而设，意为欢迎其回到
蓬莱仙岛。
LONG);

        set("exits", ([
                "east"     : __DIR__"nanshandao2",
                "west"     : __DIR__"xiuzhenchi",
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
