// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIG "连绵不绝" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int attack_time, i;
        int level;


        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("hanbing-mianzhang", 1) < 100)
                return notify_fail("你寒冰绵掌不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "hanbing-mianzhang")
                return notify_fail("你没有激发寒冰绵掌，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "hanbing-mianzhang")
                return notify_fail("你没有准备寒冰绵掌，难以施展" + name() + "。\n");

        if ((int)query("neili", me) < 250)
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = me->query_skill("strike");
        dp = target->query_skill("parry");

        level = me->query_skill("hanbing-mianzhang", 1);

        msg = HIC "\n$N" HIC "双掌陡然连续拍出，掌风阴寒无比，一招"
              "「" HIG "连绵不绝" HIC "」，已连连罩向$n" HIC "。\n" NOR;
        message_combatd(msg, me, target);

        attack_time += 3 + random(ap / 40);

        if (attack_time > 7)
                attack_time = 7;

        addn("neili", -attack_time*30, me);
        addn_temp("apply/attack", level/2, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (! target->is_busy() && random(3) == 1)
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->start_busy(1 + random(attack_time));
        addn_temp("apply/attack", -level/2, me);

        return 1;
}