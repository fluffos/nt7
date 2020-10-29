#include <ansi.h>
#include <combat.h>

string name() { return HIR "血浪滔天" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");

        if (me->query_skill("tiexue-dao", 1) < 100)
                return notify_fail("你铁血刀法等级不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "tiexue-dao")
                return notify_fail("你没有激发铁血刀法，难以施展" + name() + "。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的内功修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你目前的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "杀气大盛，手中" + weapon->name() +
              HIR "一振，顿时一道血光从刀锋闪过，将$n"
              HIR "团团裹住。\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                           HIR "只听$n" HIR "一声惨嚎，嗤啦一声，"
                                           "一股血柱自" HIR "血色刀影中激射而出。"
                                           "\n" NOR);
                me->start_busy(2);
                addn("neili", -120, me);
        } else
        {
                msg += CYN "可是$n" CYN "眼明手快，奋力招架，将$N"
                       CYN "的招式全部挡开。\n" NOR;
                me->start_busy(3);
                addn("neili", -80, me);
        }
        message_combatd(msg, me, target);

        return 1;
}