#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "擒龙手" NOR; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手使用。\n");

        if( !objectp(weapon=query_temp("weapon", target)) )
                return notify_fail("对方没有使用兵器，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 260)
                return notify_fail("你内功修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你内力修为不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("dragon-strike", 1) < 180)
                return notify_fail("你降龙十八掌火候不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "dragon-strike")
                return notify_fail("你没有激发降龙十八掌，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "dragon-strike")
                return notify_fail("你没有准备降龙十八掌，难以施展" + name() + "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你现在真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "暴喝一声，全身内劲迸发，气贯右臂奋力外扯，企图将$n"
              HIR "的" + weapon->name() + HIR "吸入掌中。\n" NOR;

        ap = attack_power(me, "strike") + me->query_str()*10;
        dp = defense_power(target, "parry") + target->query_int()*10;

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -300, me);
                msg += HIR "$n" HIR "只觉周围气流涌动，手中" + weapon->name()
                       + HIR "竟然拿捏不住，向$N" HIR "掌心脱手飞去。\n" NOR;
                me->start_busy(2);
                weapon->unequip();
                weapon->move(me, 1);
        } else
        {
                addn("neili", -200, me);
                msg += CYN "$n" CYN "只觉周围气流涌动，慌忙中连将手中"
                       + weapon->name() + CYN "挥舞得密不透风，使得$N"
                       CYN "无从下手。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}
