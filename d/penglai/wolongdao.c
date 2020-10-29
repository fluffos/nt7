inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "卧龙道");
        set("long",@LONG
卧龙道位于蝶仙谷与飞龙谷之间，是连接两处的要道，传说仙
界曾派出巨龙守护这里的道口，为的是防止谷中飞龙出谷，危害人
间。可不想那巨龙偷懒睡熟，让那飞龙逃出山谷。后来巨龙得到仙
界惩罚，变做化石，卧在此路之上，终身守护飞龙谷，此道便以卧
龙道命名。
LONG);

        set("exits", ([
                "west"     : __DIR__"diexiangu2",
                "east"     : __DIR__"jinxianqiao",        
                "south"    : __DIR__"changshengdao2",                
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛
        set("objects", ([ 
                "/clone/npc/walker": 2,
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
