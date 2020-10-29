inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "飞龙谷");
        set("long",@LONG
这里便是居住着飞龙的飞龙谷，不时地有一些飞龙向你飞来发
出震耳欲聋的叫声，令人毛骨悚然。难怪天界会派巨龙守护峡谷，
不让这些飞龙出谷危害人间，凡人见之早已经心胆惧烈，哪里是这、
厮的对手。
LONG);

        set("exits", ([
                "north"     : __DIR__"changshengdao2",        
                "south"     : __DIR__"feilonggu2",                
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛

        set("n_time", 120); 
        set("n_npc", 1); 
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/feilong");
        
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
