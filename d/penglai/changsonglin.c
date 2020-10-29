inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "长松林");
        set("long",@LONG
蓬莱仙岛的长松林中生长着许多高大的松树，每当有仙气涌向
这里的时候，松树上的松鼠便会不停地摇动树枝，松叶也纷纷落下，
将地上铺得软软的。
LONG);

        set("exits", ([
                "north"     : __DIR__"xiuzhenchi",
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛

        set("n_time", 20); 
        set("n_npc", 2); 
        set("n_max_npc", 10);
        set("s_npc", __DIR__"npc/songshu");
                
        if (random(3) == 1)
        {
                set("objects", ([
                        __DIR__"obj/songye" : 1 + random(10),
                ]));
        }
                        
        set("region", "penglai");
        setup();
}

void init ()
{
        if (! playerp(this_player()))return;
        
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
