#include <ansi.h>
#include <combat.h>

string name() { return HIW "太极初升" NOR; }

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
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if (me->query_skill("force") < 80)
                return notify_fail("你的内功的修为不够，难以施展" + name() + "。\n");

        if (me->query_skill("wudang-jian", 1) < 60)
                return notify_fail("你的武当剑法修为不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "wudang-jian")
                return notify_fail("你没有激发武当剑法，难以施展" + name() + "。\n");

        if( query("neili", me)<50 )
                return notify_fail("你现在真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "凝神聚气，手中" + weapon->name() +
              HIW "回转，划出一个闪亮的剑圈，套向$n" HIW "而去。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -30, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "不明剑理，一个不慎，登时被$N"
                                           HIR "划中，鲜血直流！\n" NOR);
        } else
        {
                addn("neili", -20, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "微微一笑，轻轻格挡开了$P"
                       CYN "的剑招。\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}