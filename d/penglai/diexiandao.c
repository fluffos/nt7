inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "蝶仙道");
        set("long",@LONG
来到此处犹如进入了梦幻般的世界，周围零星一只五彩斑斓的
蝴蝶围绕在你身体周围，前方光彩闪耀，一条大道直通山谷之中。       
LONG);

        set("exits", ([
                "west"     : __DIR__"tianxiandao3",
                "east"     : __DIR__"diexiangu1",                        
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
                set("penglai", 1);           // 表示在蓬莱岛

                set("objects", ([ 
                        "/clone/npc/walker": 1,
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
