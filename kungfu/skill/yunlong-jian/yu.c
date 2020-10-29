// yu.c 以气驭剑
// by Lonely

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
                return notify_fail("以气驭剑绝技只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");
                
        if( (int)me->query_skill("yunlong-jian", 1) < 50 )
                return notify_fail("你的云龙剑法不够娴熟，不会使用「以气驭剑」。\n");
                                
        if( (int)me->query_skill("yunlong-shengong", 1) < 50 )
                return notify_fail("你的云龙神功不够高，不能用来反震伤敌。\n");
                        
        if( query("neili", me)<500 )
                return notify_fail("你现在内力太弱，不能使用「以气驭剑」。\n");
                
        if( target->is_busy() )
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧ⅵ\n");
        
        msg = HIC "$N微微一笑，猛吸一口气,欲使出以气驭剑绝技攻击$n。\n"NOR;
        
        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                
                addn("neili", 400, me);
                pmsg = HIR"只见$N手中剑光幻作一条金龙,腾空而起,倏的罩向$n,\n$n只觉一股大力铺天盖地般压来,登时眼前一花，两耳轰鸣,哇的喷出一口鲜血！！\n"NOR;
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50, pmsg);
                me->start_busy(2);
        } else 
        {
                msg += CYN"可是$p猛地向前一跃,跳出了$P的攻击范围。\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
