// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "定阳针" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("quanzhen-jian", 1) < 100)
                return notify_fail("你全真剑法不够娴熟，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你现在内力太弱，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "quanzhen-jian")
                return notify_fail("你没有激发全真剑法，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "脚下左弓右箭，神气完足如雷霆五岳，一式「"
              HIR "定阳针" NOR + HIC "」斜斜刺出。\n" NOR;

        me->start_busy(2);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "看到$N" HIR "这气拔千钧"
                                           "的一击，竟不知如何招架，登时受了重创"
                                           "！\n" NOR);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企图，斜跃避开。\n" NOR;
                addn("neili", -30, me);
        }
        message_combatd(msg, me, target);

        return 1;
}