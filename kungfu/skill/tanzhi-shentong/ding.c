#include <ansi.h>
#include <combat.h>

string name() { return HIC "定昆仑" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int fmsk;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if ((int)me->query_skill("tanzhi-shentong", 1) < 120)
                return notify_fail("你的弹指神通不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("你没有激发弹指神通，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("你没有准备弹指神通，难以施展" + name() + "。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "合指轻弹，顿时只听“飕”的一声，一缕若有若无的"
              "罡气已朝$n" HIC "电射而去。\n" NOR;

        ap = attack_power(me,"finger");
        dp = defense_power(target,"parry");
        fmsk = me->query_skill("qimen-xuanshu", 1); 

        if (ap / 2 + random(ap) + fmsk > dp) 
        {
                msg +=  HIR "$n" HIR "只觉胁下一麻，已被$P"
                        HIR "指气射中，全身酸软无力，呆立当场。\n" NOR;
                target->start_busy(ap / 90  + fmsk / 25); 
                me->start_busy(1);
                addn("neili", -100, me);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN
                       "的企图，轻轻一跃，跳了开去。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
