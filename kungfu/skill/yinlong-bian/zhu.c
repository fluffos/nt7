#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIC "天诛龙蛟诀" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不对。\n");

        if (me->query_skill("force", 1) < 130)
                return notify_fail("你的内功火候不够，使不了" + name() + "。\n");

        if (me->query_skill("yinlong-bian", 1) < 100)
                return notify_fail("你的银龙鞭法功力太浅，使不了" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真气不够，无法使用" + name() + "。\n");

        if (me->query_skill_mapped("whip") != "yinlong-bian")
                return notify_fail("你没有激发银龙鞭法，使不了" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "诡异的一笑，手中" + weapon->name() +
              HIW "犹如一条银龙猛然飞向$n" HIW "，正是九阴真经中的"
             "绝招「" HIC "天诛龙蛟诀" HIW "」！\n" NOR;

        ap = attack_power(me, "whip") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");
                addn("neili", -200, me);
                me->start_busy(2);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85,
                                           HIR "结果$n" HIR "一声惨叫，未能看破$N"
                                           HIR "的企图，被这一鞭硬击在胸口，鲜血飞"
                                           "溅，皮肉绽开！\n" NOR);
                message_combatd(msg, me, target);

        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "飞身一跃而起，躲避开了"
                       CYN "$P" CYN "的攻击！\n" NOR;
                message_combatd(msg, me, target);
        }

        return 1;
}