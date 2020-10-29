// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "幻剑诀" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if (me->query_skill("tianyu-qijian", 1) < 120)
                return notify_fail("你的天羽奇剑不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill("force", 1) < 160)
                return notify_fail("你的内功火候不足，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        level = me->query_skill("tianyu-qijian", 1);

        msg = HIY "$N" HIY "凝神息气，手腕疾抖，挽出千万个剑花，铺天盖地飞向$n"
              HIY "。\n" NOR;

        message_combatd(msg, me, target);
        addn("neili", -100, me);
        addn("apply/attack", level/2, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn("apply/attack", -level/2, me);
        me->start_busy(1 + random(2));

        return 1;
}
