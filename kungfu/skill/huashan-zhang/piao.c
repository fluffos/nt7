
#include <ansi.h>
#include <combat.h>

string name() { return HIG "飞絮飘渺" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");

        if ((int)me->query_skill("huashan-zhang", 1) < 30)
                return notify_fail("你的华山掌法不够娴熟，不会使用" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "huashan-zhang")
                return notify_fail("你没有准备使用华山掌法，无法施展" + name() + "。\n");

        if( query("neili", me)<60 )
                return notify_fail("你现在真气不够，无法施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIM "\n猛然间$N" HIM "双掌不断拍向$n" HIM "出，风声呼呼，攻到途中忽又左\n"
              "手虚出右手作势欲发，虚虚实实，飘渺不定，正是华山绝招「" HIG  "飞絮飘渺" HIM
              "」。 \n顷刻剑$n" HIM "已被$N" HIM "掌风笼罩。\n" NOR;

        addn("neili", -30, me);
        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "结果$p" HIR "一时无法辨别其中虚实，竟无法施招。\n" NOR;
                target->start_busy(ap / 90 + 2);
        } else
        {
                msg += CYN "可是$n" CYN "看破其中虚实，更不理会。\n" NOR;
                me->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}