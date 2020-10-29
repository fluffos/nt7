#include <ansi.h>
#include <combat.h>

#define KAI "「" WHT "混沌初开" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;
        
        if( userp(me) && !query("can_perform/baisheng-quan/kai", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(KAI "只能对战斗中的对手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("只有空手才能施展" KAI "。\n");

        if ((int)me->query_skill("baisheng-quan", 1) < 100)
                return notify_fail("你的百胜神拳不够娴熟，难以施展" KAI "。\n");

        if ((int)me->query_skill("force") < 140)
                return notify_fail("你的内功修为不够，难以施展" KAI "。\n");

        if (me->query_skill_mapped("cuff") != "baisheng-quan") 
                return notify_fail("你没有激发百胜神拳，难以施展" KAI "。\n");

        if (me->query_skill_prepared("cuff") != "baisheng-quan")
                return notify_fail("你没有准备百胜神拳，难以施展" KAI "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在的真气不足，难以施展" KAI "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = WHT "$N" WHT "身子蓦的横移，两臂向后反钩，呼的一声朝$n"
              WHT "攻去，正是「" NOR + HIR "混沌初开" NOR + WHT "」绝"
              "技。\n" NOR;
              
        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");
        
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "cuff");
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "结果$n" HIR "闪避不及，$N" HIR "双"
                                           "拳正中$p" HIR "头部两侧，顿时口喷鲜血"
                                           "，几欲昏厥。\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -60, me);
                msg += CYN "可是$p" CYN "识破了$P"
                       CYN "这一招，斜斜一跃避开。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}