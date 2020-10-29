#include <ansi.h>
#include <combat.h>

#define JISHI "「" HIB "即世即空" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if( userp(me) && !query("can_perform/weituo-zhang/jishi", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JISHI "只能对战斗中的对手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail(JISHI "只能空手施展。\n");

        if ((int)me->query_skill("weituo-zhang", 1) < 120)
                return notify_fail("你韦陀掌不够娴熟，难以施展" JISHI "。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的内功修为不够，难以施展" JISHI "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不够，难以施展" JISHI "。\n");

        if (me->query_skill_mapped("strike") != "weituo-zhang") 
                return notify_fail("你没有激发韦陀掌，难以施展" JISHI "。\n");

        if (me->query_skill_prepared("strike") != "weituo-zhang")
                return notify_fail("你没有准备韦陀掌，难以施展" JISHI "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIB "只见$N" HIB "双掌一错，揉身而进，连环攻出数掌，一环环"
              "向$n" HIB "劈去。\n" NOR;

        if (random(me->query_skill("strike")) > target->query_skill("dodge") / 2)
        {
                me->start_busy(2);
                damage = me->query_skill("strike");
                damage = damage / 2 + random(damage / 2);
                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 20,
                                           HIR "$n" HIR "一惊，被$N" HIR "掌劲重重的击"
                                           "在胸前，登时呕出一口鲜血！\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -30, me);
                msg += CYN "可是$p" CYN "识破了$P"
                       CYN "这一招，斜斜一跃避开。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
