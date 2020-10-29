#include <ansi.h>
#include <combat.h>

string name() { return WHT "浊流剑" NOR; }

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

        if (me->query_skill("force") < 200)
                return notify_fail("你的内功的修为不够，难以施展" + name() + "。\n");

        if (me->query_skill("shangqing-jian", 1) < 140)
                return notify_fail("你的上清剑法修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "shangqing-jian")
                return notify_fail("你没有激发上清剑法，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = WHT "只见$N" WHT "手中" + weapon->name() + WHT "一抖，施出上清剑法"
              "「浊流剑」，霎时无数剑光罩向$n" WHT "！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -100, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "$n" HIR "只感剑光夺目，顿时眼花缭"
                                           "乱，被$N" HIR "一剑刺中，鲜血飞溅。\n"
                                           NOR);
        } else
        {
                addn("neili", -50, me);
                me->start_busy(3);
                msg += CYN "可是$n" CYN "看破" CYN "$N"
                       CYN "的招数，飞身一纵，避开了这"
                       "一剑。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}