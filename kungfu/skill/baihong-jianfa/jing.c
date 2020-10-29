// This program is a part of NITAN MudLIB
// jingtian.c  白虹惊天 

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, ob;
        string msg;

        if (! me->is_fighting())
                return notify_fail("「白虹惊天」只能在战斗中使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                        return notify_fail("你使用的武器不对。\n");

        if ((int)me->query_skill("shenghuo-xuanming", 1) < 100)
                return notify_fail("你的圣火玄冥功火候还不到家, 不能使用这一绝技 !\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本剑法火候还不到家, 不能使用这一绝技 !\n");

        if ((int)me->query_skill("baihong-jianfa", 1) < 100)
                return notify_fail("你的逍遥剑法火候还不到家, 不能使用这一绝技 !\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真气不够！\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力修为不够！\n");

        msg = HIC "\n$N长啸一声，手弹长剑，身形飘忽不定，使的正是白虹惊剑法的绝技「白虹惊天」！\n" NOR;
        message_combatd(msg, me);

        me->clean_up_enemy();
        ob = me->select_opponent();
        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),0);
        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),0);
        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),0);
        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),0);

        addn("neili", -random(150)-50, me);
        me->start_busy(1 + random(4));      
        return 1;
}