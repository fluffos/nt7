inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "长生道");
        set("long",@LONG
长生道象征着长生不老，传说，这岛上不但居住着仙者， 
还居住着凡间之人，至于这些人从何而来便不得而知。只知
道他们长年居住在长生村中。也有传说，凡是踏过长生道的
人便可以获得永生。不知道这里为什么也叫长生道，据说这
里长生村的居民原本打算在这里定居，后来谷中出现飞龙后
全村的人便搬离了这里。
LONG);

        set("exits", ([
                "north"         : __DIR__"wolongdao",        
                "south"         : __DIR__"feilonggu1",
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛
        set("no_fight", 1);

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
