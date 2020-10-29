// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "若悲" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if ((int)me->query_skill("mingwang-jian", 1) < 100)
                return notify_fail("你不动明王剑不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "mingwang-jian")
                return notify_fail("你没有激发不动明王剑，难以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "手中的" + weapon->name() + HIW "轻轻递出，"
              "发出一阵轻鸣，$n" + HIW "听了心中不禁有些迷茫。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "心头一震，一时竟然沉迷当中，忘记了"
                       "继续攻击。\n" NOR;
                target->start_busy(ap / 90 + 2);
                me->start_busy(1);
        } else
        {
                msg += HIC "可是$n" HIC "神智只是略微一滞，随即清醒，没"
                       "有被$P" HIC "所困扰。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
