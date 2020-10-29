// tengshe.c 腾蛇

#include <ansi.h>
#include <combat.h>

string name() { return WHT "腾蛇诀" NOR; }

inherit F_SSERVER;

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

        if ((int)me->query_skill("xiewei-bian", 1) < 100)
                return notify_fail("你使用的武器不对，无法施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，无法施展" + name() + "。\n");

        if (me->query_skill_mapped("whip") != "xiewei-bian")
                return notify_fail("你没有激发蝎尾鞭，无法施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = WHT "$N" WHT "陡然施展出「腾蛇」诀，手腕轻轻一抖，" + weapon->name() +
              WHT "顿时拔地弹起，如同活物一般悄然袭向$n" + WHT "！\n" NOR;

        ap = attack_power(me, "whip") + me->query_skill("force");
        dp = defense_power(target, "force") + target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");
                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "然而$n" HIR "未能看破企图，一声惨嚎，"
                                           + weapon->name() + HIR "鞭端已没入体内半寸"
                                           "，登时连退数步！\n" NOR);
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "运足内力，奋力挡住了"
                       CYN "$P" CYN "这神鬼莫测的一击！\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}