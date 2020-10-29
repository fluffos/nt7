#include <ansi.h>
#include <combat.h>

string name() { return HIW "风雨交加" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, count;
        int i, attack_time;
        int skill;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("longcheng-shendao", 1) < 120)
                return notify_fail("你的龙城神刀不够娴熟，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force", 1) < 150)
                return notify_fail("你的内功修为不足，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "longcheng-shendao")
                return notify_fail("你没有激发龙城神刀，难以施展" + name() + "。\n");

        if( query("neili", me)<270 )
                return notify_fail("你目前的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "大喝一声，施出绝招「" HIW "风雨交加" HIC "」手"
              "中的" + weapon->name() + HIC "如雨点\n一般向$n" HIC "打去，$n" HIC
              "如同小舟一般在刀雨中漂泊不定。\n" NOR;
        
        skill = me->query_skill("longcheng-shendao", 1);
        attack_time = 3;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "dodge");

        attack_time += random(ap / 40);

        if (attack_time > 7)
                attack_time = 7;

        addn("neili", -attack_time*25, me);

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIY "这阵刀势变化莫测，$n" HIY "顿时觉得眼花缭乱，无法抵挡。\n" NOR;
                count = skill / 3;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "不禁心中凛然，不敢有半点小觑，使出浑身解数抵挡。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 20);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));

        return 1;
}
