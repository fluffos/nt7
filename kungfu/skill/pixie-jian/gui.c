#include <ansi.h>
#include <combat.h>

string name() { return HIR "鬼魅身法" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int ap, dp;
        int skill;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        skill = me->query_skill("pixie-jian", 1);

        if (skill < 100)
                return notify_fail("你的辟邪剑法不够娴熟，难以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("dodge") != "pixie-jian")
                return notify_fail("你没有准备使用辟邪剑法，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "身子忽进忽退，宛若鬼魅，身形诡秘异常，在$n"
              HIR "身边飘忽不定。\n" NOR;

        ap = attack_power(me, "dodge");

        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap*2) > dp)
        {
                msg += HIR "$p" HIR "霎时只觉眼花缭乱，只能紧守门户，不"
                       "敢妄自出击！\n" NOR;
                target->start_busy(ap / 80 + 2);
                me->start_busy(1);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的身法，并没有受"
                       "到任何影响。\n" NOR;
                me->start_busy(2);
        }
        addn("neili", -50, me);
        message_combatd(msg, me, target);

        return 1;
}
