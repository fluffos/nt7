inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "南山之颠");
        set("long",@LONG
南山之颠乃南山最高峰，不少仙者常来这里吸收天地的灵气以
促进仙法的修炼。你站在高峰之上，远眺蓬莱仙岛，其景美不胜收，
实在难以用人间任何语言来描述。俯瞰南山，依然是如此神秘，若
隐若现，时高时低。翘首东望麒麟崖，更是令人充满无尽的遐思。
LONG);

        set("exits", ([
                "down"    : __DIR__"nanshanjiaoxia",
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛

        set("n_time", 600 + random(180)); 
        set("n_npc", 1); 
        set("n_max_npc", 8);
        set("s_npc", __DIR__"npc/dacaishen");
        
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
        
        if( playerp(this_player()) && !query("penglai/nanshan_quest/ok", this_player()) )
        {
                tell_object(this_player(), HIG "\n你被一阵仙气卷下山去 ……！。\n" NOR);
                this_player()->move(__DIR__"nanshanjiaoxia");
        }
        else // 第一次南山之颠获取一些奖励
        {
                if( !query("penglai/nanshanzhidian_quest/ok", this_player()) )
                {
                        tell_object(this_player(), HIR "\n你找到南山之颠峰并吸收了这里的天地灵气，获得了5万点潜能及10万点实战体会奖励。\n\n" NOR);
                        addn("potential", 50000, this_player());
                        addn("experience", 100000, this_player());
                        set("penglai/nanshanzhidian_quest/ok", 1, this_player());
                        this_player()->save();
                }                
        }
}
