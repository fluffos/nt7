// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "骄阳劈天" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (userp(me) && !query("can_learn/jiuyang-shengong/enable_weapon", me))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "blade")
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("jiuyang-shengong", 1) < 220)
                return notify_fail("你的九阳神功不够娴熟，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force", 1) < 260)
                return notify_fail("你的内功根基不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("blade", 1) < 260)
                return notify_fail("你的基本刀法火候不够，难以施展" + name() + "。\n");

        if ((int)query("max_neili", me) < 5500)
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if (query("neili", me) < 400)
                return notify_fail("你现在真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "jiuyang-shengong")
                return notify_fail("你没有激发九阳神功为刀法，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "\n$N" HIW "猛然间飞身而起，半空中一声长啸，内力源源不绝地涌"
              "入" + weapon->name() + HIW "，刹那间刀芒夺目，自天而下，劈向$n" HIW "！\n" NOR;

        addn("neili", -150, me);
        ap = attack_power(me, "blade") + me->query_skill("force", 1);
        dp = defense_power(target, "parry") + target->query_skill("force", 1);

        me->start_busy(2 + random(2));
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                damage+= query("jiali", me);
                damage *= 4;
                addn("neili", -200, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85 + random(50),
                                           (: final, me, target, damage :));
        } else
        {
                msg += HIC "可是$n" HIC "看透$P" HIC "此招之中的破绽，镇"
                       "定逾恒，全神应对自如。\n" NOR;
        }
        message_sort(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        addn("neili", -(damage/4), target);
        addn("neili", -(damage/8), target);
        return  HIR "$n" HIR "只觉刀芒夺目，正犹豫间到刀芒已穿透$n" HIR "身体，顿时"
                "鲜血狂涌，内息散乱。\n" NOR;
}
