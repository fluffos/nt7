#include <ansi.h>
#include <combat.h>

string name() { return HIY "降魔" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("mingwang-jian", 1) < 140)
                return notify_fail("你不动明王剑不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "mingwang-jian")
                return notify_fail("你没有激发不动明王剑，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "纵身跃入半空，将全身劲气贯于" + weapon->name() +
              HIY "中，剑尖顿时吐出一股剑气直指$n" HIY "而去。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "只见一道黄芒闪过，微作差"
                                           "异，登时只觉全身一麻，剑气已透胸而过！"
                                           "\n" NOR);
        } else
        {
                addn("neili", -50, me);
                me->start_busy(3);
                msg += CYN "可是$n" CYN "一声冷笑，飞身一跃而起，避开"
                       CYN "$N" CYN "发出的剑气。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
