#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "截筋断脉" NOR; }

int perform(object me)
{
        string msg;
        object target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        skill = me->query_skill("jieshou-jiushi", 1);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if (skill < 100)
                return notify_fail("你的截手九式等级不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的内力不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("hand") != "jieshou-jiushi")
                return notify_fail("你没有激发截手九式，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("hand") != "jieshou-jiushi")
                return notify_fail("你现在没有准备使用截手九式，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "身形一展，陡然跃至$n" HIR "跟前，十指箕张，直锁$n"
              HIR "要穴，正是截手九式绝技「截筋断脉」。\n" NOR;

        ap = attack_power(me, "hand");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -200, me);
                me->start_busy(3);

                damage = damage_power(me, "hand");

                target->receive_damage("jing", damage);
                target->receive_wound("jing", damage);
                target->receive_damage("qi", damage * 3 / 2);
                target->receive_wound("qi", damage * 3 / 2);
                if( !target->is_busy() )
                        target->start_busy(1);

                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK,
                       damage, 10, HIR "$n" HIR "奋力格挡，可还是被$N"
                                   HIR "截住腕部要穴，只觉眼前一黑，"
                                   "几欲晕倒。\n" NOR);
        }
        else
        {
                addn("neili", -100, me);
                msg += CYN "$n" CYN "见状大吃一惊，急忙向后猛退数步，"
                       "终于避开了$N" CYN "这一击。\n" NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        return 1;
}
