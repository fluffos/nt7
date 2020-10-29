inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "飞马崖");
        set("long",@LONG
飞马乃岛中仙者的主要坐骑，这里便是飞马生长的地方。据说，
每过几年仙者便回来这里挑选新的飞马。传说，这飞马与寻常之马
不同，其主要饲料来源于金色沙滩的金沙，只有喂实金沙飞马才能
生长。放眼望去，悬崖四周一群飞马正飞行，追逐嬉戏。
LONG);

        set("exits", ([
                "down"    : __DIR__"nanshanjiaoxia",
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛

        set("n_time", 180); 
        set("n_npc", 1); 
        set("n_max_npc", 6);
        set("s_npc", __DIR__"npc/feima");
        
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
        
        if( userp(this_player()) && !query("penglai/nanshan_quest/ok", this_player()) )
        {
                tell_object(this_player(), HIG "\n你被一阵仙气卷下山去 ……！。\n" NOR);
                this_player()->move(__DIR__"nanshanjiaoxia");
        }
        else // 第一次飞马崖增加ridding 5LV
        {
                if( !query("penglai/feimaya_quest/ok", this_player()) )
                {
                        tell_object(this_player(), HIR "\n你仔细观察飞马的一举一动，对骑术有了新的理解。\n" NOR);
                        tell_object(this_player(), HIC "你的「骑术」进步了！\n\n" NOR);
                        this_player()->set_skill("riding", this_player()->query_skill("riding", 1) + 5);
                        set("penglai/feimaya_quest/ok", 1, this_player());
                        this_player()->save();
                }
        }
}
