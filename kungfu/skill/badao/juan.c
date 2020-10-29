#include <ansi.h>
#include <combat.h>

#define CHAN "「" HIC "龙卷风" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int level;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(CHAN "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对，难以施展" CHAN "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if ((level = me->query_skill("badao", 1)) < 500)
                return notify_fail("你的霸刀不够娴熟，难以施展" CHAN "。\n");

        if (me->query_skill_mapped("blade") != "badao")
                return notify_fail("你没有激发霸刀，难以施展" CHAN "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在真气不够，难以施展" CHAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "负刀而立，猛然间，刀锋一转，一股强劲的刀气奔腾而出，犹如龙卷风般呼啸而至，将$n" HIC "笼罩。\n" NOR;

        addn("neili", -300, me);
        if (random(level) + 200 > (int)target->query_skill("dodge", 1) / 2)
        {
                msg += HIR "结果$p" HIR "被$P" HIR "闹个手忙脚乱，"
                       "惊慌失措，呆在当场，不知如何应对！\n" NOR;
                target->start_busy(level / 20 + 5);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企图，镇"
                       "定逾恒，全神应对自如。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}