#include <ansi.h>
#include <combat.h>

string name() { return HIR "五指刀" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int i, count;
        int fmsk = me->query_skill("tiezhang-shuishangpiao", 1);

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("tie-zhang", 1) < 180)
                return notify_fail("你铁掌掌法火候不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "tie-zhang")
                return notify_fail("你没有激发铁掌掌法，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "tie-zhang")
                return notify_fail("你没有准备铁掌掌法，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 280)
                return notify_fail("你的内功修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<2800 )
                return notify_fail("你的内力修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = WHT "$N" WHT "身形一展，施出铁掌绝技「" HIR "五指刀" NOR +
              WHT "」，掌锋激起层层气浪，朝$n" WHT "狂劈而去。\n" NOR;

        ap=attack_power(me,"strike")+me->query_str()*10;
        dp=defense_power(target,"parry")+target->query_dex()*10;

        if (ap / 2 + random(ap) + fmsk > dp)
        {
                msg += HIR "$n" HIR "面对$N" HIR "这排山倒海般的攻"
                       "势，完全无法抵挡，招架散乱，连连退后。\n" NOR;
                count = ap / 10;
        } else
        {
                msg += HIC "$n" HIC "心底微微一惊，心知不妙，急忙"
                       "凝聚心神，竭尽所能化解$N" HIC "数道掌力。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        addn_temp("apply/attack", count+fmsk, me);
        addn_temp("apply/unarmed_damage", count*2+fmsk, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, TYPE_LINK);
        }
        addn("neili", -250, me);
        me->start_busy(1 + random(2));
        addn_temp("apply/attack", -count-fmsk, me);
        addn_temp("apply/unarmed_damage", -count*2-fmsk, me);
        return 1;
}
