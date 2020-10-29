inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "麒麟崖");
        set("long",@LONG       
麒麟乃传说中瑞兽之一，古代传说中麒麟与龙、凤、龟合为四
灵，乃毛类动物之王。麒麟很少在人间出没，所以凡间也也少有人
见过麒麟。这里是一处绝壁，向南望去是宽阔的大海，向北俯瞰飞
龙谷，谷中飞龙也不过巴掌般大小。偶然，可见绝壁之上有身影晃
动，不知是不是传说中的麒麟兽。谷底一片烟雾缠绕，缕缕金光从
谷底射在崖壁之上，闪耀着眩目的光彩，据说，这谷底藏着一只千
年仙鼠，恐怕已修成人形了吧。你突然觉得浑身轻飘飘的，有一种
想从这里跳（tiao）下去的冲动。
LONG);

        set("exits", ([
                "northdown"     : __DIR__"feilonggu2",                                
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛

        set("n_time", 600 + random(180)); 
        set("n_npc", 1); 
        set("n_max_npc", 6);
        set("s_npc", __DIR__"npc/jinseqilin");
        
        set("region", "penglai");
        setup();
}

void init ()
{
        add_action("do_tiao", "tiao");

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

int do_tiao(string arg)
{
        object me = this_player();

        message_vision(HIW "\n$N" HIW "深吸一口气，纵身跳下麒麟崖 ……\n", me);
        
        if (random(2))
        {
                tell_object(me, HIG "突然间，你只觉得浑身飘忽，被一阵仙气卷走 ……\n" NOR);
                me->move(__DIR__"bianqueju");
                return 1;
        }
        tell_object(me, HIY "如你所料，这里的仙气能够支撑起你自身的重量，慢慢的飘落到谷底 ……\n\n" NOR);
        
        me->move(__DIR__"gudi");

        return 1;         
}
