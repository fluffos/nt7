// This program is a part of NITAN MudLIB
// zhui.c  追命

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg, pmsg;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「追命」只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");
                
        if( (int)me->query_skill("jinshe-jian", 1) < 150 )
                return notify_fail("你的金蛇剑法不够娴熟，不会使用。\n");
                                
        if( query("neili", me)<800 )
                return notify_fail("你现在内力太弱，不能使用「追命」。\n");
                        
        msg = HIY "$N微微一笑，剑意若有若无，$n却感到莫大的压力。\n"NOR;

        me->want_kill(target);
        if( !target->is_killing(me) ) 
                target->kill_ob(me);
        
        ap=me->query_skill("sword")*3/2+query("level", me)*20+
             me->query_skill("martial-cognize", 1);
        dp=target->query_skill("force")+query("level", target)*20+
             target->query_skill("martial-cognize", 1);

        if (ap / 2 + random(ap) > dp)
        {
                if (! target->is_busy())
                target->start_busy( random(2) + 2);
                
                damage = (int)me->query_skill("jinshe-jian", 1) / 2;
                
                addn("neili", -400, me);
                pmsg = HIR "只见$N剑走了个怪异的弧线，从不可思议的角度向$n杀去,\n$n只觉得背心一阵冰凉，呆呆地看着前胸的剑尖！\n" NOR;
                
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40, pmsg);
                me->start_busy(2);
        } else 
        {
                msg += CYN"可是$p猛地向前一跃,跳出了$P的攻击范围。\n"NOR;
                addn("neili", -200, me);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}
