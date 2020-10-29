// moxiao.c 魔笑

#include <ansi.h>

inherit F_SSERVER;

string name() { return "魔笑"; }

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
                return notify_fail("「魔笑」只能对战斗中的对手使用。\n");

        skill = me->query_skill("tianmo-jian", 1);

        if (skill < 150)
                return notify_fail("你的天魔剑法修为有限，现在不能使用「魔笑」！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真气不够，无法运用「魔笑」！\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你只有装备剑才能施展「魔笑」！\n");

        msg = HIR "$N" HIR "突然间身形连转，口中发出阵阵凄厉的怪笑，$n"
              HIR "只觉耳中有如针刺，不禁心乱神迷，攻势顿缓。\n$N"
              HIR "蓦的扑到$n" HIR "近前，手中的" + weapon->name() +
              HIR "一振，瞬间已向$p刺出数剑。\n" NOR;

        message_combatd(msg, me, target);
        count = skill / 2;
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))  break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(3));
        addn_temp("apply/attack", -count, me);

        return 1;
}
