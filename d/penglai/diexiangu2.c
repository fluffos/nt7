inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "蝶仙谷");
        set("long",@LONG
进入蝴蝶谷，成群的彩蝶飞绕在你四周，而阵阵花香扑鼻而来，
五彩的光环由天际投射而来，将这里照射得分外美丽。令你觉得置
身如此美景，所有凡尘琐事都已抛之脑后。    
LONG);

        set("exits", ([
                "west"     : __DIR__"diexiangu1",
                "east"     : __DIR__"wolongdao",        
                "south"    : __DIR__"diexianju",                
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛

        set("n_time", 45); 
        set("n_npc", 1); 
        set("n_max_npc", 7);
        set("s_npc", __DIR__"npc/xiaodiexian");
        
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
