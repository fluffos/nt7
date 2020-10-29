// huashen.c 化身万千

#include <ansi.h>

inherit F_SSERVER;

string name() { return "化身万千"; }

int perform(object me, object target)
{
        string msg;
        object weapon;
        int i;
        int skill;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「化身万千」只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你只有空手才能使用「化身万千」。\n");

        skill = me->query_skill("tianmo-zhang", 1);

        if (skill < 120)
                return notify_fail("你的天魔掌法修为太低，现在不能使用「化身万千」！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真气不够，无法使出「化身万千」！\n");

        msg = HIC "$N" HIC "突然身形变快，双掌翻飞幻化出无数掌影，一股巨大"
              HIC "的气浪连绵不断，一层接一层压向$n" HIC "。\n" NOR;

        message_combatd(msg, me, target);
        count = skill / 3;
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(target))  break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(3));
        addn_temp("apply/attack", -count, me);

        return 1;
}
