inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "金仙桥");
        set("long",@LONG
金仙桥乃是连接卧龙谷与金色沙滩的一座桥梁，桥下流水潺潺，
泛着金光。据说，原本这里的流水清澈无比，后来海水主讲将金色
沙滩的金沙冲到金仙桥下，这流水便成了金色。这里的水经过金色
沙滩的净化和仙气的洗涤变成了可以引用的淡水，如果有容器可以
在这里装一壶（fill）尝尝。
LONG);

        set("exits", ([
                "west"     : __DIR__"wolongdao",
                "east"     : __DIR__"jinseshatan",                
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛
        set("resource/water", 1);    // 可以加水

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
