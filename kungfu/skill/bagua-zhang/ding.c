#include <ansi.h>
#include <combat.h>


#define DING "「" HIY "背心钉" NOR "」"

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if( userp(me) && !query("can_perform/bagua-zhang/ding", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DING "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(DING "只能空手施展。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的内功修为不够，难以施展" DING "。\n");

        if ((int)me->query_skill("bagua-zhang", 1) < 80)
                return notify_fail("你的八卦掌不够娴熟，难以施展" DING "。\n");

        if (me->query_skill_mapped("strike") != "bagua-zhang") 
                return notify_fail("你没有激发八卦掌，难以施展" DING "。\n");

        if (me->query_skill_prepared("strike") != "bagua-zhang") 
                return notify_fail("你没有准备八卦掌，难以施展" DING "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在真气不够，难以施展" DING "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "身形一转，已飘至$n" HIY "身后，陡然施出一招「背心"
              "钉」，单手作锥，直插$n" HIY "背心要穴！\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
        
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "strike");
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "结果$p" HIR "闪避不及，被$P" HIR
                                           "这招插中，掌劲顿时透胸而过，口喷鲜血"
                                           "，几乎摔倒！\n" NOR);
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