// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return WHT "象跌势" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp;
        int i, count;
        string msg;
        int fmsk = me->query_skill("mizong-zhenyan", 1);

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("longxiang-gong", 1) < 240)
                return notify_fail("你的龙象般若功修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "longxiang-gong")
                return notify_fail("你没有激发龙象般若功为拳脚，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "longxiang-gong")
                return notify_fail("你没有激发龙象般若功为内功，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "longxiang-gong")
                return notify_fail("你没有准备使用龙象般若功，难以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "蓦地收回双掌，施出密宗绝学「" NOR + WHT "象跌势"
              HIY "」，双臂再度横移，猛贯向$n" HIY "！\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_con()*10;
        dp = defense_power(target, "parry") + target->query_dex()*10;

        if (ap / 2 + random(ap) > dp)
        {
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIR "$n" HIR "全然无力阻挡，竟被$N"
                                HIR "一拳击得飞起，重重的跌落在地上。\n" NOR;
                        addn("neili", -50, me);
                        me->start_busy(1);

                        message_combatd(msg, me, target);

                        target->receive_damage("qi", 100, me);
                        set("eff_qi", 1, target);
                        set("eff_jing", 1, target);
                        target->unconcious(me);

                        me->start_busy(1 + random(2));
                        return 1;
                } else
                {
                        count = ap / 10;
                        msg += HIR "$n" HIR "见$P" HIR "来势迅猛之极，一时不知该如"
                                "何作出抵挡，竟呆立当场。\n" NOR;
                }
        } else
        {
                msg += HIY "$n" HIY "见$p" HIY "来势迅猛之极，甚难防备，连"
                       "忙振作精神，小心抵挡。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);

        addn("neili", -300, me);

        for (i = 0; i < 5 + fmsk / 100; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, TYPE_LINK);
        }

        me->start_busy(1 + random(3));
        addn_temp("apply/attack", -count, me);

        return 1;
}
