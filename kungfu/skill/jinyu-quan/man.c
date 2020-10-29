// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "金玉满堂" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("jinyu-quan", 1) < 80)
                return notify_fail("你的金玉拳法不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("cuff") != "jinyu-quan")
                return notify_fail("你没有激发金玉拳法，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "jinyu-quan")
                return notify_fail("你没有准备金玉拳法，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "双拳纷飞，气势如虹，顿时幻出一片拳影，似乎$n"
              HIY"的全身都被拳影所笼罩。\n" NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "cuff");

                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "结果只听“砰砰砰砰”几声闷响，$p"
                                           HIR "前胸被$P" HIR "轰中数拳，登时呕出"
                                           "一口鲜血！\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -50, me);
                msg += CYN "可是$p" CYN "识破了$P"
                       CYN "这一招，斜斜一跃避开。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
