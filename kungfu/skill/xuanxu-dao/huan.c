#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "乱环决"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「乱环决」只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的内功的修为不够，不能使用乱环决！\n");

        if (me->query_skill("xuanxu-dao", 1) < 135)
                return notify_fail("你的玄虚刀法修为不够，目前不能使用乱环决！\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真气不够，不能使用乱环决！\n");

        msg = HIW "$N" HIW "使出玄虚刀法中的绝技乱环决，刀出成环，环环相连，只绞的$n" + HIW
             "眼前一片影环。\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -180, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "就听见“喀喀喀”几声脆响，$p" HIR "一声"
                                           "惨叫，全身各处骨头被刀环一一绞断，像滩软泥般"
                                           "塌了下去！\n" NOR );
        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "奋力格挡，$P" CYN
                       "只觉得精力略有衰竭，手中刀光渐缓。 \n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
