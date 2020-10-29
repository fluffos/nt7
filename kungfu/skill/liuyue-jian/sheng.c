// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "天升剑诀" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, skill;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的内功的修为不够，难以施展" + name() + "。\n");

        if (me->query_skill("liuyue-jian", 1) < 140)
                return notify_fail("你的流月剑舞修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "liuyue-jian")
                return notify_fail("你没有激发流月剑舞，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "手腕一阵疾抖，剑身微颤，剑作龙吟。刹那间剑芒陡涨，"
              "如天河倒泻一般洒向$n"
              HIW "。\n" NOR;

        message_combatd(msg, me, target);
        addn("neili", -100, me);
        skill = me->query_skill("liuyue-jian", 1);
        addn("apply/attack", skill/3, me);
        addn("apply/damage", skill*3, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn("apply/attack", -skill/3, me);
        addn("apply/damage", -skill*3, me);
        me->start_busy(1 + random(3));

        return 1;
}