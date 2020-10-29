inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "会仙道");
        set("long",@LONG
这里是每一百年一次的蟠桃盛会群仙会聚的地方，此处非常宽
阔，仙气大盛，夹杂着蟠桃园中飘出的清香，令人产生无限的遐想。
LONG);

        set("exits", ([
                "north"    : __DIR__"pantaoyuan1",
                "south"    : __DIR__"lancaodi1",        
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
