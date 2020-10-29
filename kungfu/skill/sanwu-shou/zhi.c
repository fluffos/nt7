#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "无所不至" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time, level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "whip" )
                return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");

        if ((level=me->query_skill("sanwu-shou", 1)) < 100)
                return notify_fail("你三无三不手不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("whip") != "sanwu-shou")
                return notify_fail("你没有激发三无三不手，难以施展" + name() + "。\n");

        if( query("neili", me)<140 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIM "\n$N" HIM "长啸一声，腾空而起，施出绝招 「" HIW "无"
              "所不至" HIM "」，\n手中" + weapon->name() + HIM "化出无数"
              "光点，犹如满天花雨般洒向$n全身各处" HIM "。" NOR;

        message_combatd(msg, me, target);

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");
        attack_time = 4;

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIR "结果$n" HIR "被$N" HIR "攻了个措手不及，$n"
                      HIR "慌忙招架，心中叫苦。\n" NOR;
                count = level / 4;
                attack_time += random(ap / 45);
                addn_temp("apply/attack", count, me);
        } else
        {
                msg= HIC "$n" HIC "见$N" HIC "这几鞭招式凌厉，凶猛异"
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
        me->start_busy(1 + random(4));

        return 1;
}