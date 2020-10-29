// ding.c 全真剑-定阳针

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("定阳针只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if( (int)me->query_skill("quanzhen-jianfa", 1) < 40 )
                return notify_fail("你的全真剑法不够娴熟，不能使用定阳针。\n");

        if( (int)me->query_skill("quanzhen-xinfa", 1) < 40 &&
            (int)me->query_skill("yunv-xinfa", 1) < 40 )
                return notify_fail("你的本门内功不够娴熟，不能使用定阳针。\n");

        if( query("neili", me)<150 )
                return notify_fail("你现在内力太弱，不能使用定阳针。\n");

        msg = HIC "$N脚下左弓右箭，神气完足如雷霆五岳，一式「定阳针」斜斜刺出。\n"NOR;

        //if( !target->is_killing(me) ) target->kill_ob(me);

        if (random(me->query_skill("force")) > target->query_skill("force")/2 )
        {
                me->start_busy(2);

                damage = (int)me->query_skill("quanzhen-jianfa", 1) + (int)me->query_skill("force",1);
                //(全真剑法级别+基本内功)

                damage = damage/2 + random(damage/2);

                target->receive_damage("qi", damage);
                target->start_busy(4);
                addn("neili", -100, me);

                msg += HIR"$n看到$N这气拔千钧的一击，竟不知如何招架！\n"NOR;

        }
        else
        {
                me->start_busy(3);
                msg += CYN"可是$p看破了$P的企图，斜跃避开。\n"NOR;
        }
        message_vision(msg, me, target);

        return 1;
}
