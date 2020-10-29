#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "剑舞千秋" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("miaojia-jian", 1) < 160)
                return notify_fail("你苗家剑法不够娴熟，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 220 )
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<1800 )
                return notify_fail("你的内力修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "miaojia-jian")
                return notify_fail("你没有激发苗家剑法，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "手中" + weapon->name() + HIY "一声龙吟，三十七势苗"
              "家剑连环施出，将$n" HIY "罩在剑光之中。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        attack_time = 5;
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$p" HIR "只见得剑光万道，顿时被$P" HIR
                       "凌厉的剑招攻得应接不暇，连连后退！\n" NOR;
                count = ap / 10;
                addn_temp("apply/attack", count, me);
                addn_temp("apply/damage", count, me);
                attack_time += random(ap / 200);
        } else
        {
                msg += HIC "$n" HIC "见$N" HIC "剑势汹涌，霍霍剑光"
                       "逼人而来，不敢大意，小心应付。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        if (attack_time > 8)
                attack_time = 8;

        addn("neili", -attack_time*25, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(1 + random(3));

        return 1;
}