#include <ansi.h>
#include <combat.h>

#define HONG "「" HIY "轰雷万钧" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg, wp;
        int ap, dp, damage;

        if( userp(me) && !query("can_perform/dali-chu/hong", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target ) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HONG "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "hammer" )
                return notify_fail("你所使用的武器不对，难以施展" HONG "。\n");

        if (me->query_skill_mapped("hammer") != "dali-chu")
                return notify_fail("你没有激发无上大力杵，难以施展" HONG "。\n");

        if ((int)me->query_skill("dali-chu", 1) < 80)
                return notify_fail("你无上大力杵火候不足，难以施展" HONG "。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的内功火候不足，难以施展" HONG "。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的内力修为不足，难以施展" HONG "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在的真气不足，难以施展" HONG "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        wp = weapon->name();

        msg = HIR "$N" HIR "舞动手中" + wp + HIR "，一招「" HIY "轰雷万钧"
              HIR "」挟着震天撞击之声朝$n" HIR "当头砸下！\n" NOR;

        ap = me->query_skill("hammer");
        dp = target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -150, me);
                damage = ap / 3 + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "见$N" HIR "来势汹涌，心"
                                           "知不妙，可已然不及躲避，被这锤击中胸"
                                           "口，吐血连连。\n" NOR);
                me->start_busy(3);

        } else
        {
                msg += CYN "可是$p" CYN "早知$P"
                       CYN "有此一着，当即巧妙招架，格挡开来。\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}