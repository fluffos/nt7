// zhi.c 幽冥神指

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
 
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("幽冥神指只能在战斗中对对手使用。\n");

        if (me->query_skill("kuihua-mogong", 1) < 150)
                return notify_fail("你的葵花魔功还不够娴熟，不能使用幽冥神指！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真气不够！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "进步欺前，随即一指无声无息的向$n" HIR "的要害刺出！\n";

        me->want_kill(target);
        ap = me->query_skill("kuihua-mogong", 1);
        dp=query("combat_exp", target)/10000;
        addn("neili", -60, me);
        me->start_busy(1 + random(2));

        if (dp >= 100)
        {
                msg += HIC "$n" HIC "知道来招不善，急忙闪避，没出一点差错。\n" NOR;
        } else
        if (random(ap) > dp)
        {
                msg += HIR "这一招速度之快完全超出了$n" HIR "的想象，被$N"
                       HIR "这一指正好刺中了丹田要害，浑身真气登时涣散！\n" NOR;
                message_combatd(msg, me, target);
                target->die(me);
                return 1;
        } else
        {
                msg += HIM "$n" HIM "大吃一惊，连忙退后，居然"
                      "侥幸躲开着这一招！\n" NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}