#include <ansi.h>
#include <combat.h>

#define QIAN "「" HIW "千剑纵横势" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(QIAN "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" QIAN "。\n");

        if ((int)me->query_skill("wushen-jian", 1) < 200)
                return notify_fail("你的衡山五神剑不够娴熟，难以施展" QIAN "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真气不够，难以施展" QIAN "。\n");

        if (me->query_skill_mapped("sword") != "wushen-jian")
                return notify_fail("你没有激发衡山五神剑，难以施展" QIAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "\n$N" HIW "运转衡山五神剑，手中" + weapon->name() +
              HIW "迸出无数剑光，宛若飞虹擎天，席卷$n" HIW "而去。" NOR;

        message_sort(msg, me, target);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        attack_time = 4;

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIR "结果$n" HIR "被$N" HIR "攻了个措手不及，$n"
                      HIR "慌忙招架，心中叫苦。\n" NOR;

                count = ap / 10;
                attack_time += random(ap / 45);
        } else
        {
                msg = HIC "$n" HIC "见$N" HIC "这几剑招式凌厉，凶猛异"
                      "常，只得苦苦招架。\n" NOR;
                count = 0;
        }
            message_combatd(msg, me, target);

        if (attack_time > 9)
                attack_time = 9;

        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count*2, me);
        addn("neili", -attack_time*30, me);
        me->start_busy(1 + random(attack_time / 2));

        set_temp("perform_wushenjian/qian", 1, me);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                       break;

                if (! target->is_busy() && random(3) == 1)
                       target->start_busy(1);
 
                COMBAT_D->do_attack(me, target, weapon, TYPE_LINK);
        }
        delete_temp("perform_wushenjian/qian", me);

        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count*2, me);
        return 1;
}
