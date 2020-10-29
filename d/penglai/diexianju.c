inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "蝶仙居");
        set("long",@LONG
一来到这里，花香袭来，仔细一看，才知道这居所竟是用各种
花瓣堆砌而成，红橙粉兰，各种颜色纵横交汇，芬芳艳丽。房间中
央，一名年亲貌美的仙子正在将死去的蝴蝶制作成标本。想必这便
是传说中的蝶仙了。
LONG);

        set("exits", ([        
                "north"    : __DIR__"diexiangu2",                
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛
        set("no_fight", 1);
        
        set("objects", ([
                __DIR__"npc/diexian" : 1,
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
