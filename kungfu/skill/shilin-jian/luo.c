#include <ansi.h>
#include <combat.h>

#define LUO "「" HIW "落英纷飞" NOR "」"

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
                return notify_fail(LUO "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不对，难以施展" LUO "。\n");

        if ((int)me->query_skill("shilin-jian", 1) < 120)
                return notify_fail("你石廪剑法不够娴熟，难以施展" LUO "。\n");

        if (me->query_skill_mapped("sword") != "shilin-jian")
                return notify_fail("你没有激发石廪剑法，难以施展" LUO "。\n");

        if( query("neili", me)<140 )
                return notify_fail("你现在的真气不够，难以施展" LUO "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "长啸一声，手中" + weapon->name() + HIY "化出"
              "无数剑光，剑势如虹，连连刺向$n" HIY "。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        attack_time = 4;

        if (ap / 2 + random(ap * 2) > dp)
        {
                msg += HIR "结果$n" HIR "被$N" HIR "攻了个措手不及，$n"
                       HIR "慌忙招架，心中叫苦。\n" NOR;
                count = ap / 8;
                attack_time += random(ap / 45);
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "见$N" HIC "这几剑招式凌厉，凶猛异"
                       "常，只得苦苦招架。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        if (attack_time > 7)
                attack_time = 7;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(attack_time));

        return 1;
}