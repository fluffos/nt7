#include <ansi.h> 
#include <combat.h> 

#define RU "「" HIR "我入地狱" NOR "」" 

inherit F_SSERVER; 

string final(object me, object target, int damage); 

int perform(object me, object target) 
{
        object weapon; 
        string msg; 
        int ap, dp; 
        int damage; 
        int fmsk = me->query_skill("lunhui", 1);
        
        if (! target) target = offensive_target(me); 

        if (! target || ! me->is_fighting(target)) 
                return notify_fail(RU "只能对战斗中的对手使用。\n"); 

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" RU "。\n"); 

        if ((int)me->query_skill("lunhui-jian", 1) < 200) 
                return notify_fail("你的释迦轮回剑法不够娴熟，难以施展" RU "。\n"); 

        if( query("neili", me)<200 )
                return notify_fail("你现在真气不够，难以施展" RU "。\n"); 

        if ((int)me->query_skill("buddhism", 1) < 200) 
                return notify_fail("你现在对佛学领悟不够，难以施展" RU "。\n"); 

        if (me->query_skill_mapped("sword") != "lunhui-jian")  
                return notify_fail("你没有激发释迦轮回剑，难以施展" RU "。\n"); 

        if (! living(target)) 
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n"); 

        msg = HIC "$N" HIC "气贯手中长剑，一剑去势沉稳，缓缓的扫向$n" 
              "，看似变化平平。\n" NOR; 

        addn("neili", -80, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");
        
        if (target->is_bad()) ap += ap / 10; 

        me->start_busy(2); 
        ap *= 2;
        if (ap / 2 + random(ap) > dp) 
        {
                damage = damage_power(me, "sword");
                damage = query("jiali", me);
                damage *= 6;
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 375+fmsk/15, 
                                           (: final, me, target, damage :)); 
        } else 
        {
                msg += HIC "可是$n" HIC "见识广博" HIC "，以料到$P剑法的变化" 
                       "，全神应对。\n" NOR; 
        } 
        message_combatd(msg, me, target); 

        return 1; 
}

string final(object me, object target, int damage) 
{
        target->receive_damage("jing", damage / 4, me); 
        target->receive_wound("jing", damage / 8, me); 
        return  HIC "$n" HIC "见剑势平平，丝毫未把这招放在眼里，忽然$N" 
                HIC "剑势一变，手中长\n剑竟荡起层层涟漪，一波一波的逼向$n！\n" NOR + 
                HIR "$n" HIR "对这变化毫无防范，顿时被$P" HIR "这一剑扫中" 
                "，一股血柱自剑芒中激射而出！\n" NOR; 
}
