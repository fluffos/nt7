// qianqianbiao.c                       心有千千镖

#include <weapon.h>
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("心有千千镖" NOR, ({"biao"}));
        set_weight(50);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("long", "这是一枚四川唐门秘制的暗器，威力无比。\n");
                set("value", 0);
        }
        setup();
}

void init()
{
        add_action("do_perform","use");
}

int do_perform(string arg)
{
        object me, target;
        string msg;

        me = this_player();
        
        me->clean_up_enemy();
        target = me->select_opponent();

        if ( !arg || arg != "qian")
                return 0;
        
        if ( !(me->is_fighting()) )
                return notify_fail("心有千千镖只能在战斗中使用。\n");
 
        if( (int)me->query_skill("tangmen-throwing", 1) < 180 )
                return notify_fail("你的唐门暗器手法不够娴熟，无法使用心有千千镖。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的内力修为不够，无法使用心有千千镖。\n");

        if( query_temp("xinqian", me) )
                return notify_fail("你忙于战斗，无法分神使用心有千千镖了。\n");

        if( query("neili", me)<1500 )
                return notify_fail("你的内力不够。\n");
        
        if( query("yanli", me)<100 )
                return notify_fail("你的眼力太差了，目标不精确！\n");       

        msg = HIR"\n$N突然身行一止，从怀中摸出一枚手掌大小的暗器，一扬手向$n掷去。\n只见$n的周身飞舞着无数的光影，却听不到一丝声音。\n"NOR;
        message_vision(msg, me, target);
        addn("neili", -1500, me);
        set_temp("xinqian", 1, me);

        tell_object(target, HIR"\n你急忙屏气凝神，希望能够躲开这致命的一击。\n"NOR);
        target->start_busy(6);

        remove_call_out("effect_biao");
        call_out("effect_biao", 8, me, target);

        return 1;
}

int effect_biao(object me, object target)
{
        int myskill, trskill;
        string msg;

        myskill = (int) (2 * (int)me->query_skill("dodge") + (query("combat_exp",me) / 1000) + (int)me->query_skill("tangmen-biaofa", 1)); 
        trskill = (int) (2 * (int)target->query_skill("dodge") + (query("combat_exp",target) / 1000)); 

        if ( ( myskill >= trskill ) && ( random(100) != 0 ) )
                {
                        msg = HIR"忽然那无数的光影一闪而没，$n身行一顿，喷出一口鲜血，仰天而倒。\n"NOR;
                        message_vision(msg, me, target);
                        tell_object(target, HIR"你只觉得胸口一阵钻心的疼痛。低头一看只见那枚暗器已经深深的嵌在你的心口。\n血迹中隐约有几个小字[心有千千...]。"NOR);
                        delete_temp("xinqian", me);
                        me->start_busy(5);
                        this_object()->move(target);
                        target->unconcious();
                }
        else
                {
                        tell_object(target, HIR"忽然那无数的光影一闪而没，你心中一惊急忙运内力于全身。\n"NOR);
                        msg = HIR"$n双臂急舞，衣袖带起破风之声。只听当的一声轻响，竟将那枚暗器磕飞开去。\n"NOR;
                        message_vision(msg, me, target);
                        if( query("neili", target)<800 )
                                set("neili", 0, target);
                        else
                                addn("neili", -1000, target);
                        delete_temp("xinqian", me);
                        me->start_busy(3);
                        destruct(this_object());
                }
        return 1;
}