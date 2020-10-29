// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIM "赤心连环决" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int attack_time, i;
        int v, level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((level = me->query_skill("chilian-shenzhang", 1)) < 100)
                return notify_fail("你赤练神掌不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "chilian-shenzhang")
                return notify_fail("你没有准备赤练神掌，难以施展" + name() + "。\n");

        if (me->query_skill("force") < 100)
                return notify_fail("你的内功修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        msg = HIC "$N" HIC "暗运内功，但见$N" HIC "双掌微微呈显"
              "赤色，陡然连续反转，\n使出一招「" HIM "赤心连环决" HIC
              "」，掌风凌厉，将$n" HIC "笼罩在双掌之中。\n" NOR;

        message_combatd(msg, me, target);

        ap *= 2;
        if (ap / 2 + random(ap) > dp)
        {
                msg = HIR "$n" HIR "心中一惊，却被$N" HIR "掌"
                      "风所困，顿时阵脚大乱。\n" NOR;
                v = level;
        } else
        {
                v = 0;
                msg = HIY "$n" HIY "看清$N" HIY "这几招的来路，但"
                      "内劲所至，掌风犀利，也只得小心抵挡。\n" NOR;
        }
        message_combatd(msg, me, target);

        attack_time += 4 + random(ap / 100);

        if (attack_time > 6)
                attack_time = 6;

        addn("neili", -attack_time*20, me);

        addn_temp("apply/attack", v, me);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn_temp("apply/attack", -v, me);
        me->start_busy(2 + random(4));

        return 1;
}
