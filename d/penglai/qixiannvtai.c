inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "七仙女台");
        set("long",@LONG
这里是一处高耸的平台，传说，七仙女常在这里修炼仙法。放
眼望去，天际之处，一道彩虹划空而过，七位美貌无比的仙女正翩
翩起舞，舞姿婀娜，如此美景，令人留恋忘返。
LONG);

        set("exits", ([
                "down"    : __DIR__"nanshanjiaoxia",
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛

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
        
        if( !query("penglai/nanshan_quest/ok", this_player()) )
        {
                tell_object(this_player(), HIG "\n你被一阵仙气卷下山去 ……！。\n" NOR);
                this_player()->move(__DIR__"nanshanjiaoxia");
        }
        else // 第一次七仙女台增加容貌1点
        {
                if( !query("penglai/qixiannvtai_quest/ok", this_player()) && query("per", this_player())<30 )
                {
                        tell_object(this_player(), HIR "\n你看到了七仙女起舞的盛景，受益不浅。\n" NOR);
                        tell_object(this_player(), HIC "你的「容貌」提升了！\n\n" NOR);                        
                        CHANNEL_D->do_channel(this_object(), "rumor", "听说" HIY + this_player()->name() + "(" + 
                                                             query("id", this_player())+")"HIM"在蓬莱仙岛"
                                                             "看到了七仙女起舞的盛景，受益不浅。\n" NOR);   
                        addn("per", 1, this_player());
                        set("penglai/qixiannvtai_quest/ok", 1, this_player());
                        this_player()->save();
                }
        }
}
