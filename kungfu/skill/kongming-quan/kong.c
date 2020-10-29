// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIG "空空如也" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("kongming-quan", 1) < 150)
                return notify_fail("你的空明拳不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "kongming-quan")
                return notify_fail("你没有激发空明拳，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "kongming-quan")
                return notify_fail("你没有准备空明拳，难以施展" + name() + "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你现在的真气太弱，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = WHT "$N" WHT "使出空明拳「" HIG "空空如也" NOR + WHT "」，拳劲"
              "虚虚实实，变化莫测，让$n" WHT "一时难以捕捉。\n" NOR;
        addn("neili", -80, me);

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);

                damage = damage_power(me, "unarmed");
                damage+= query("jiali", me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "无法窥测$N" HIR "拳中奥"
                                           "秘，被这一拳击中要害，登时呕出一大口"
                                           "鲜血！\n:内伤@?");
        } else
        {
                me->start_busy(3);
                msg += CYN "可是$p" CYN "识破了$P"
                       CYN "的拳招中的变化，精心应对，并没有吃亏。\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
