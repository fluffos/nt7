inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "金色沙滩");
        set("long",@LONG
此处乃是蓬莱仙岛东方尽头，远处是一望无际的海洋，脚下沙
滩软绵绵的，泛着耀眼的金光，犹如佛光普照，令人无比舒泰。
LONG);

        set("exits", ([
                "west"     : __DIR__"jinxianqiao",                
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛

        set("n_time", 40); 
        set("n_npc", 1); 
        set("n_max_npc", 8);
        set("s_npc", __DIR__"npc/xiaocaishen");
        
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
