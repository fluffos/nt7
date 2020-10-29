// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "天下无狗" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, count;
        int i, attack_time;
        int delta;
        int fmsk = me->query_skill("bixue-danxin", 1);

        if( query("wugou", me)<500 )
                return notify_fail("你还没有受过高人指点，无法施展" + name() + "。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if (me->query_skill("dagou-bang", 1) < 220)
                return notify_fail("你打狗棒法不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("staff") != "dagou-bang")
                return notify_fail("你没有激发打狗棒法，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功火候不足，难以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "手中" + weapon->name() + HIW "一卷，带"
              "起阵阵风声，犹若千百根相似，层层叠叠将$n" HIW "笼罩"
              "其中。\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "parry");
        
        delta = ABILITY_D->check_ability(me, "ap_power-dgb-tian"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        attack_time = 5;

        ap *= 2;
        if (ap / 2 + random(ap) + fmsk / 2 > dp)
        {
                msg += HIR "$n" HIR "只觉眼花缭乱，发现四面八方皆是杖"
                       "影，心底寒意顿生，招架散乱。\n" NOR;
                count = ap / 5 + fmsk;
                addn_temp("apply/attack", count, me);
                addn_temp("apply/damage", count, me);
                attack_time += random(ap / 90);
        } else
        {
                msg += HIY "$n" HIY "只觉眼前一花，发现四面八方皆是杖"
                       "影，急忙收敛心神，仔细招架。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        if (attack_time > 12)
                attack_time = 12;
        
        attack_time += fmsk / 125;
        addn("neili", -attack_time*30, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, TYPE_LINK);
        }
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(2 + random(3));

        return 1;
}
