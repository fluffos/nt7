inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "麒麟崖底");
        set("long",@LONG
到得此处，举头一望，原来麒麟崖竟如此挺拔，直冲云霄，令
人惊叹。崖底风景秀丽，绿树葱郁，生机勃勃。几只不只名的飞鸟
在你头顶盘旋，不远处有一块圆形的石头，走近一看，犹如镜面一
般将天际处的光芒汇聚于此，投射到四周。不远处有一根树藤，可
以顺着爬（pa）上麒麟崖。
LONG);

        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛
        set("no_fight", 0);
                
        set("region", "penglai");
        setup();
}

void init ()
{        
        add_action("do_pa", "pa");
        
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

int do_pa(string arg)
{
        object me = this_player();
        
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正在忙着呢。\n");
        
        message_vision(HIY "$N" HIY "施展轻功，顺着树藤及仙气的浮力，轻松地爬上麒麟崖 ……\n", me);
        
        me->move(__DIR__"qilinya");
        
        return 1;
                
}
