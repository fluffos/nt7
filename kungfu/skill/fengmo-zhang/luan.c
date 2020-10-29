// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "群魔乱舞" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int lvl;
        int i, ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你所使用的武器不对，难以施展"+name()+"。\n");

        if ((lvl = (int)me->query_skill("fengmo-zhang", 1)) < 120)
                return notify_fail("你疯魔杖法火候不够，难以施展"+name()+"。\n");

        if (me->query_skill_mapped("staff") != "fengmo-zhang")
                return notify_fail("你没有激发疯魔杖法，难以施展"+name()+"。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候不够，难以施展"+name()+"。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在的真气不足，难以施展"+name()+"。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "只见$N" HIR "眼中杀气大盛，暴喝一声，飞扑上前，"
                  "便如发狂一般，手中的" + weapon->name() +
              HIR "化出数道残影，一齐打向$n" HIR "！\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {

                msg += HIY "$n" HIY "见$N" HIY "这等声势，早已无心恋"
                       "战，一时不知应该如何抵挡，唯有连连后退。\n" NOR;
                count = lvl / 10;
                addn_temp("apply/attack", count, me);
        } else
                count = 0;

        message_combatd(msg, me, target);
        addn("neili", -100, me);

        for (i = 0; i < 3; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2) && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(5));
        return 1;
}