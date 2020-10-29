inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "长生梅林");
        set("long",@LONG
此处是蓬莱仙岛的梅林，由于离长生村很近，所以取命
为长生梅林。走到这里，梅花的扑鼻之香早已浸透全身各处
令人身心舒畅无比。据说，这里的梅花每隔一段时间会掉落
在地上，有些梅花吸收了这里的仙气便会逐渐成长，最终变
成一种叫青梅的果实。而用青梅加上其他材料酿成的青梅酒
乃是人间绝对品尝不到的。
LONG);

        set("exits", ([
                "southwest"    : __DIR__"caiyunjian2",        
                "northeast"    : __DIR__"changshengmeilin2",
                "east"         : __DIR__"changshengdao1",                
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛
        
        set("n_time", 20); 
        set("n_npc", 2); 
        set("n_max_npc", 10);
        set("s_npc", __DIR__"npc/xique");
                
        if (random(2) == 1)
        {
                if (random(2) == 1)
                        set("objects", ([
                                __DIR__"obj/meihua" : 1 + random(3),
                        ]));
                else
                        set("objects", ([
                                __DIR__"obj/qingmei" : 1 + random(4),
                        ]));                        
        }
        
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
