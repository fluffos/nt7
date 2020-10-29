inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "扁鹊居");
        set("long",@LONG
据说，凡是在蓬莱仙岛的凡人在意外死亡后魂魄都不会离开身
体，而是被岛上的仙气带来这里，神医扁鹊会将这些人起死回生。
四周看起古香古色，桌椅摆设也非常简单，奇怪的是这里并没有任
何医治病人的药具。 
LONG);

        set("exits", ([        
                "south"    : __DIR__"diexiangu1",                
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛
        set("no_fight", 1);
        
        set("objects", ([
                __DIR__"npc/bianque" : 1,
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
