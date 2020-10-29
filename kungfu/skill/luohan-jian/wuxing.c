//来去若无形 wuxing.c

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

//inherit F_CLEAN_UP;

void remove_effect(object me, int a_amount, int d_amount);

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int skill;
        int extra;
        string msg;
        
        if( userp(me) && !query("can_perform/luohan-jian/wuxing", me) )
                return notify_fail("你所使用的外功中没有这样的功能。\n");

        if ( !target ) target = offensive_target(me);

        if ( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「来去若无形」只能在战斗中使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("「来去若无形」必须用剑才能施展。\n");

        if( (int)me->query_skill("luohan-jian", 1) < 120 )
                return notify_fail("你的「罗汉剑法」不够娴熟，不会使用「来去若无形」。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的内力不够。\n");

        skill = me->query_skill("luohan-jian",1);

        extra = me->query_skill("luohan-jian",1) / 10;
        extra += me->query_skill("luohan-jian",1) / 10;
        addn_temp("apply/attack", extra, me);
        addn_temp("apply/damage", extra, me);

        msg = HIG "$N身行突变，瞬间犹如分出无数身影闪电般的向$n攻去！\n" NOR;
               message_vision(msg, me, target); 
        
        addn("neili", -200, me);
        
        message_combatd(HIR "  来字决！\n" NOR, me, target); 
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),
                                       TYPE_REGULAR); 

        message_combatd(HIY "    去字决！\n" NOR, me, target); 
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),
                                       TYPE_REGULAR); 

        message_combatd(HIG "      若字决！\n" NOR, me, target); 
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),
                                       TYPE_REGULAR); 
        
        message_combatd(HIB "        无字决！\n" NOR, me, target); 
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),
                                       TYPE_REGULAR); 
        
        message_combatd(HIW "          形字决！\n" NOR, me, target); 
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),
                                       TYPE_REGULAR); 

        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, skill, 50, 
                    HIC "            来去若无形    幻化无真境 \n" NOR);
        message_combatd(msg, me, target); 

        me->start_busy(3);
        addn_temp("apply/attack", -extra, me);
        addn_temp("apply/damage", -extra, me);

        return 1;
}
