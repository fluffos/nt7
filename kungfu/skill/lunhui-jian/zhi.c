#include <ansi.h> 

#define CHAN "「" HIR "神剑指穴" NOR "」" 

inherit F_SSERVER; 

int perform(object me, object target) 
{ 
        object weapon; 
        string msg; 
        int ap, dp;

        if (! target) 
        { 
                me->clean_up_enemy(); 
                target = me->select_opponent(); 
        }

        if (! target || ! me->is_fighting(target)) 
                return notify_fail(CHAN "只能对战斗中的对手使用。\n"); 

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" CHAN "。\n"); 

        if (target->is_busy()) 
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n"); 

        if ((int)me->query_skill("force") < 180) 
                return notify_fail("你的内功火候不够，难以施展" CHAN "。\n"); 

        if ((int)me->query_skill("lunhui-jian", 1) < 120) 
                return notify_fail("你的释迦轮回剑还不到家，难以施展" CHAN "。\n"); 

        if (me->query_skill_mapped("sword") != "lunhui-jian") 
                return notify_fail("你没有激发释迦轮回剑，难以施展" CHAN "。\n"); 

        if( query("neili", me)<100 )
                return notify_fail("你的真气不够，难以施展" CHAN "。\n"); 

        if (! living(target)) 
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n"); 

        msg = HIY "$N" HIY "内息澎湃，手中" + weapon->name() + HIY "遥遥指向$n，" 
              "一股劲气自"+ weapon->name() + HIY "上激射而出，直指向$n的周身大穴。\n" NOR; 
        
        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        if (target->is_bad()) ap += ap / 10; 
        
        if (ap / 2 + random(ap) > dp) 
        {
                msg += HIR "$n" HIR "稍不留神，身上几处要穴已被内力透过"
                       "，一时间无法动弹。\n" NOR; 
                target->start_busy(ap / 90 + 2); 
                addn("neili", -60, me);
                me->start_busy(1); 
        } else 
        {
                msg += CYN "可是$n" CYN "小心应对，丝毫不乱，纵身" 
                       "跃出了$N" CYN "纵横剑气的包围。\n" NOR; 
                addn("neili", -30, me);
                me->start_busy(2); 
        }
        message_combatd(msg, me, target); 

        return 1; 
}
