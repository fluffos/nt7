// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, ob;
        int extra,i,time;
        string msg;
        
        extra = me->query_skill("jinshe-jian",1);
        time = extra/40; 
        
        if( !target ) target = offensive_target(me);
        
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「金蛇万道」只能在战斗中使用。\n");
                
        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                        return notify_fail("你使用的武器不对。\n");
                        
        if( query("id", weapon) != "jinshejian" )
                return notify_fail("没有金蛇剑又怎能使出金蛇剑法的独门招式【金蛇万道】？\n");
                
        if((int)me->query_skill("sword") <200)
                return notify_fail("你的剑法修为不够， 目前不能使用【金蛇万道】! \n");
                
        weapon=query_temp("weapon", me);
        if( query("neili", me)<1000 )
                return notify_fail("你的真气不够！\n");
                
        msg = HIR  "$N猛吸一口真气，眼中神光大盛，手中的"+ weapon->name()+  HIR"急速挥舞，化作万道金虹向$n卷来！" NOR;
        message_combatd(msg,me,target);
        addn_temp("apply/attack", extra/5, me);
        addn_temp("apply/damage", extra/5, me);
        for(i=1;i<=(int)time;i++)
        {
                // msg =  YEL "$N眼中寒意幽幽，将金蛇万道发挥到最高境界！\n" NOR;
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR);
        }
        addn_temp("apply/attack", -extra/5, me);
        addn_temp("apply/damage", -extra/5, me);
        addn("neili", -500, me);
        me->start_busy(3);
        return 1;
}
