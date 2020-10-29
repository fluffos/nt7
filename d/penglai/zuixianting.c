inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "醉仙亭");
        set("long",@LONG
传说醉仙亭中常有仙者在此饮酒作乐，抚琴高歌，顺着那梵音
一路寻来。但见一中年男子坐于亭中，抚琴弹奏，琴音阵阵，犹如
天外梵音，令人心境舒泰无比。片刻那男子于弹奏间不断取出腰间
酒壶，小酌数口，自娱自乐，完全没有注意到外人的到来。
LONG);

        set("exits", ([
                "south"     : __DIR__"xiuzhenchi",
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛
        set("no_fight", 1);

        set("objects", ([
                __DIR__"npc/jiujianxian" : 1,
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
