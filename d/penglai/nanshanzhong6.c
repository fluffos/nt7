inherit DEMONROOM;

#include <ansi.h>

int i = 20;

void create()
{
        set("short", "南山中");
        set("long",@LONG
这里是蓬莱仙岛仙者修炼仙法的地方，传说南山本不存在，乃
是众仙施法而变成。四周仙气大盛，原本以为南山与普通高山无异，
却不知这里的奇幻之处。一旦进如南山之中，唯一的出路就是回到
山脚下，你站立良久才发现，所在之处并非一成不变，随着仙气地
流动，时高时低，时隐时现。有时你除了四周的仙气什么都看不见，
有时却随着此处的升高，竟可以望见东方的麒麟崖。据说，当四周
环境随着仙气不断变化的时候，可以找到去南山之颠的路，运气好
的话还会发现传说中的七仙台和飞马崖。
LONG);

        set("exits", ([
                "xunlu"    : __DIR__"nanshanzhong0",
                "out"      : __DIR__"nanshanjiaoxia",
        ]));
        
        // 南山之颠
        if (random(20) == 1)
                set("exits/nanshanzhidian",  __DIR__"nanshanzhidian");
        
        // 七仙女台和飞马崖
        if (random(10) == 1)
                set("exits/qixiannvtai", __DIR__"qixiannvtai");
        if (random(10) == 1)
                set("exits/feimaya", __DIR__"feimaya");

        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛

        set("n_time", 60); 
        set("n_npc", 1); 
        set("n_max_npc", 6);
        set("s_npc", __DIR__"npc/nianshou");
        set("objects", ([ 
                "/clone/npc/walker": 6,
        ]));
        set("region", "penglai");
        setup();
}

void init ()
{
        add_action("do_xunlu", "xunlu");
        
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

int do_xunlu()
{
        object me;
        
        me = this_player();
        
        if (me->is_busy())return notify_fail("你正忙。\n");
        
        tell_object(this_player(), HIG "\n你在南山中四处走动寻找新的道路 ...\n\n" NOR);

        me->move(__DIR__"nanshanzhong" + random(i));

        return 1;
}
