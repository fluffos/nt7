#include <ansi.h>
#include <combat.h>

#define YOU "「" HIG "罗汉伏虎" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;

        if (! target) target = offensive_target(me);

        if( userp(me) && me->query_skill("fuhu-quan",1)<100 && !query("can_perform/fuhu-quan/fuhu", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(YOU "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必须空手才能施展" YOU "。\n");

        if ((int)me->query_skill("fuhu-quan", 1) < 60)
                return notify_fail("你的伏虎拳法别不够，不会使用" YOU "。\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的内功还未娴熟，不能使用" YOU "。\n");

        if( query("neili", me)<140 )
                return notify_fail("你现在真气不够，不能使用" YOU "。\n");

        if (me->query_skill_mapped("cuff") != "fuhu-quan")
                return notify_fail("你没有激发伏虎拳法，不能施展" YOU "。\n");

        if (me->query_skill_prepared("cuff") != "fuhu-quan")
                return notify_fail("你没有准备伏虎拳法，难以施展" YOU "。\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "\n$N" HIW "步成弓形，大喝一声施出绝招「" HIG "伏虎式" HIW "」，"
              "一拳猛地击向$n" NOR"。\n" NOR;

        if (random(me->query_skill("cuff")) > target->query_skill("parry") / 2)
        {
                me->start_busy(2 + random(2));

                damage = (int)me->query_skill("cuff");
                damage = damage / 2 + random(damage / 2);

                addn("neili", -100, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40, 
                                           HIR "但见$N" HIR "一拳威猛无比，$n" HIR 
                                           "一时竟无从招架。\n" NOR);
        } else
        {
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$P" CYN
                       "的企图，稳如泰山，抬手一架格开了$P"
                       CYN "这一拳。\n"NOR;
        }
        message_sort(msg, me, target);

        return 1;
}
