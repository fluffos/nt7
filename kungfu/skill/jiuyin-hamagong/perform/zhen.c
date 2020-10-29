#include <ansi.h>
#include <combat.h>

#define ZHEN "「" WHT "蟾震九天" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int i, count;

        if( userp(me) && !query("can_perform/jiuyin-hamagong/zhen", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHEN "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(ZHEN "只能空手使用。\n");

        if ((int)me->query_skill("jiuyin-hamagong", 1) < 250)
                return notify_fail("你九阴蛤蟆功火候不够，难以施展" ZHEN "。\n");
                
        if ((int)me->query_skill("unarmed", 1) < 250)
                return notify_fail("你基本掌法没练好，难以施展" ZHEN "。\n");        

        if (me->query_skill_mapped("unarmed") != "jiuyin-hamagong")
                return notify_fail("你没有激发九阴蛤蟆功，难以施展" ZHEN "。\n");

        if (me->query_skill_prepared("unarmed") != "jiuyin-hamagong")
                return notify_fail("你没有准备九阴蛤蟆功，难以施展" ZHEN "。\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你的内功修为不够，难以施展" ZHEN "。\n");

        if( query("max_neili", me)<3500 )
                return notify_fail("你的内力修为不够，难以施展" ZHEN "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你现在的真气不足，难以施展" ZHEN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "突然伏地低嘶，心中暗念九阴蛤蟆功心法。口中冒出丝丝白气，少倾，一股真气\n"        
                  "由丹田直涌而上，$N随即猛然跃至半空，使出「 "HIY "蟾震九天" HIY "」，双掌将全身真气不停\n"

                  "击出，刹那间，飞沙走石，烟尘滚滚，劲力有如排山倒海，千军万马般往$n全身轰去。\n" NOR;  

        ap=me->query_skill("unarmed")+query("str", me)*5;
        dp=target->query_skill("parry")+query("str", target)*5;

        if( query("max_neili", me)>query("max_neili", target)*2 )
        { 
                msg += HIY "$n" HIR "全然无力阻挡，竟被$N" 
                       HIY "一拳击得飞起，重重的跌落在地上。\n" NOR; 
                addn("neili", -50, me);
                me->start_busy(1); 
 
//                message_combatd(msg, me, target); 

   
                target->start_busy(5); 
                set("qi", 1, target);
                set("eff_qi", 1, target);
  
        } else

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "\n$n" HIR "不料$N" HIR "会使出如此功力非同小可且招式诡异招式"
                       "立时招架散乱，连连出招，全身有如撕裂般痛苦，像断线风筝般弹出丈之远!\n" NOR;
                count = ap / 6;
        } else
        {
                msg += HIC "$n" HIC "自如此招非同小可，不敢小觑，急忙"
                       "收敛心神，神定气清，运足全身功力档住$N" HIC "的掌力。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count, me);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(8) < 3 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn("neili", -600, me);
        me->start_busy(1 + random(8));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/unarmed_damage", -count, me);
        return 1;
}
