#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_SSERVER;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int ap;
        int dp;
        int damage;
        string msg;

        if (target == me || ! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("你只能用寒气攻击战斗中的对手。\n");

        if (me->query_skill("bingxin-jue", 1) < 150)
                return notify_fail("你的冰心决火候不够，无法运用寒气。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的内力不够!");

        if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "默运冰心决，一股寒气迎面扑向$n"
              HIW "，四周登时雪花飘飘。\n" NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "force");

        me->start_busy(2);

        if (ap / 2 + random(ap) > random(dp))
        {
        damage = me->query_skill("bingxin-jue", 1) * me->query_skill("literate", 1) / 10;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage, me);

        damage = damage + damage / 5 * query("level", me);
                             if (random(2) && !target->is_freeze()) 
                                     target->set_freeze(random(6)+7, 0); 


/*
                if( query("neili", target)>damage )
                        addn("neili", damage, target);
                else
                        set("neili", 0, target);

*/
                msg += HIR "$n" HIR "忽然觉得一阵透骨寒意，霎时间"
                       "浑身的血液几乎都要凝固了。\n" NOR;
                target->start_busy(1);
        } else
                msg += HIY "$n" HIY "感到一阵寒意自心底泛起，连忙"
                       "运动抵抗，堪勘无事。\n" NOR;

        message_combatd(msg, me, target);

        return 1;
}
