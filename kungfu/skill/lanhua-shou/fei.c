#include <ansi.h>
#include <combat.h>

string name() { return HIC "影落飞花" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        mapping p;
        int i, af, lvl, count;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((lvl = (int)me->query_skill("lanhua-shou", 1)) < 140)
                return notify_fail("你兰花拂穴手不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("hand") != "lanhua-shou")
                return notify_fail("你没有激发兰花拂穴手，难以施展" + name() + "。\n");

        if (! mapp(p = me->query_skill_prepare())
           || p["hand"] != "lanhua-shou")
                return notify_fail("你没有准备兰花拂穴手，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "微一凝神，双手作兰花状疾拂而出，一环环的劲气登时直逼$n"
              HIC "全身各大要穴。\n" NOR;
        addn("neili", -150, me);

        ap = attack_power(me, "hand");

        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "顿时觉得眼花缭乱，全然分辨"
                       "不清真伪，只得拼命运动抵挡。\n" NOR;
                count = lvl / 3;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIY "可是$n" HIY "凝神顿气，奋力抵挡，丝"
                       "毫不受手影的干扰，。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        af = member_array("hand", keys(p));

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                set_temp("action_flag", af, me);
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->start_busy(random(3));
        addn_temp("apply/attack", -count, me);
        return 1;
}
