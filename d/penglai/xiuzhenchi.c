inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "修真池");
        set("long",@LONG
此处是岛中仙者恢复法力的修真池，池中仙气大盛，置身于此
感觉身心舒泰无比。真是快活似神仙。那熟悉已久的梵音似乎就从
北方传来，你不禁想去探个究竟。
LONG);

        set("exits", ([
                "east"      : __DIR__"yingxiandao",
                "west"      : __DIR__"xiuzhenchi2",
                "north"     : __DIR__"zuixianting",
                "south"     : __DIR__"changsonglin",
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛
        set("xiuzhenchi", 1);       // 可以提高冥思奖励
        set("no_fight", 1);
        set("sleep_room", 1);
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
