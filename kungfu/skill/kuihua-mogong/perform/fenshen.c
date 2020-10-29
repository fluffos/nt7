#include <combat.h>
#include  <ansi.h>

#define HUI "「" WHT "分身" HIW "化影" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{

        int ap, dp;
        object env;

        if( userp(me) && !query("can_perform/kuihua-mogong/fenshen", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("kuihua-mogong", 1) < 460)
                return notify_fail("你葵花魔功修为不够，难以施展" HUI "。\n");

        if( query("max_neili", me)<6000 )
                return notify_fail("你内力修为不够，难以施展" HUI "。\n");

          if( query("jingli", me)<1000 )
                return notify_fail("你精力不足，难以施展" HUI "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你内力不足，难以施展" HUI "。\n");
        
        if (me->is_busy())
                return notify_fail("你现在正忙！\n");

        if( query_temp("hiding_kuihua", me) )
                return notify_fail("你正在运功中！\n");

        ap=me->query_skill("dodge")+query("dex", me);
        dp=target->query_skill("dodge")+query("dex", target);

        env = environment(me);
        
         me->start_busy(1);
         addn("neili", -800, me);
         addn("jingli", -400, me);

        message_sort(HIY "\n$N冷笑一声，施展出《葵花宝典》记载之绝学" + HUI + HIY + 
                     "，刹那间，" + env->short() + HIY + "幻化出无数$N的身影。\n" NOR, me);
        
        if (target->query_skill("count") > 100 && random(2))
        {
                message_sort(HIC "\n$N施展出阴阳八卦的绝学，将$n的" + HUI + HIC "化解。\n" NOR, target, me);
                return 1;
        }

        if (ap / 2 + random(ap) > dp)
        {
                message_sort(HIG "\n$N顿觉眼花缭乱，失去了方向！\n" NOR, target);
                target->remove_enemy(me);
                set_temp("hiding_kuihua", 1, me);
                addn("jingli", -200, me);
                target->start_busy(4 + random(4));
                call_out("del_hiding", 20 + random(me->query_skill("kuihua-mogong", 1) / 30), me);
        }
        else
        {
                message_sort(HIM "\n$N赶紧收摄住心神，小心的移动着脚步，将$n这招化解。\n" NOR, target, me);
        }
                
        return 1;
}

void del_hiding(object me)
{

        if (! objectp(me))return;

        delete_temp("hiding_kuihua", me);

        tell_object(me, HIG "你分身化影术施展完毕，将内力收回丹田。\n");

        return;
}