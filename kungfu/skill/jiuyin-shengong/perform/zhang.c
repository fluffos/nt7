// zhang.c 九阴神掌

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("九阴神掌只能对战斗中的对手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");
                
        if ((int)me->query_skill("jiuyin-shengong", 1) < 100)
                return notify_fail("你的九阴神功不够深厚，不会使用九阴神掌。\n");

//        if (me->query_skill_prepared("strike") != "jiuyin-shengong")
        if (me->query_skill_mapped("strike") != "jiuyin-shengong")
                return notify_fail("你没有准备使用九阴神功，无法施展九阴神掌。\n");
                
        if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "双掌一错，幻化出无数掌影，层层叠荡向$n"
              HIY "逼去！\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "结果$p" HIR "被$P" HIR "逼得施展不开半点招式！\n" NOR;
                target->start_busy(ap / 80 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的掌势来路，"
                       "镇定自若，应对自如。\n" NOR;
                me->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}