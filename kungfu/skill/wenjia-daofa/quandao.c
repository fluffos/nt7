
//    /kungfu/skill/wenjia-quan/daoying.c pfm daoying
// by leontt /22/6/2000

#include <ansi.h>
inherit F_SSERVER;
int perform(object me,object target)
{
        int j = me->query_skill("wenjia-daofa", 1)/3+me->query_skill("wenjia-quan",1)/4;
        object weapon = me->query_temp("weapon");
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("拳刀合一只能对战斗中的对手使用。\n");                

        if( (int)me->query_skill("yijin-jing", 1) < 100 )
                return notify_fail("你的内功还未练成，不能使用拳刀合一！\n");    

        if( (int)me->query_skill("wenjia-daofa", 1) < 100 )
                return notify_fail("你的刀法还未练成，不能使用拳刀合一！\n");        

        if (!weapon
         || weapon->query("skill_type") != "blade"
         || me->query_skill_mapped("blade") != "wenjia-daofa")
                return notify_fail("你手里没有刀，无法使用拳刀合一！\n");

        if((int)me->query_skill("wenjia-quan", 1) < 100 )
                return notify_fail("你的拳法还未练成，不能使用拳刀合一！\n");  

        if(me->query_skill_mapped("force") != "yijin-jing")
                return notify_fail("你的内功不对，无法使用拳刀合一！\n");      

        if(me->query_skill_mapped("cuff") != "wenjia-quan" 
         || me->query_skill_prepared("cuff") != "wenjia-quan")
                return notify_fail("你没有用掌，无法使用拳刀合一！\n");

        if(me->query_skill_mapped("parry") != "wenjia-quan")
         if(me->query_skill_mapped("parry") != "wenjia-daofa")
                return notify_fail("你的招架功夫不对，无法使用拳刀合一！\n");

        if((int)me->query("max_neili") < 1200 )
                return notify_fail("你现在内力修为不够，不能使用拳刀合一！\n");      

        if((int)me->query("neili") < 600 )
                return notify_fail("你现在内力不足，不能使用拳刀合一！\n");      

        if((int)me->query_skill("blade", 1) < 100 )
                return notify_fail("你的基本刀法不够娴熟，不能在刀招中夹杂使用拳刀合一。\n");

        if((int)me->query_skill("cuff", 1) < 100 )
                return notify_fail("你的基本掌法不够娴熟，不能在刀招中夹杂使用拳刀合一。\n");     

        message_vision(HIC"\n$N大吼一声使出温家绝技「拳刀合一」，只见$P刀中带圈,狂风暴雨般攻向$n！\n"NOR, me,target);
        me->add("neili", -200); 
        me->add("jingli", -50);
        me->start_perform(4,"拳刀合一");  
        me->add_temp("apply/attack", j); 
        me->add_temp("apply/dodge",j);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
        if(objectp(target) && me->is_fighting(target))
        {
                weapon->unequip(); 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
                weapon->wield(); 
        }
        if(objectp(target) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
        if(objectp(target) && me->is_fighting(target))
        {
                weapon->unequip(); 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
                weapon->wield();
        }
        if(objectp(target) && me->is_fighting(target) && random((int)me->query_str()) > 30)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
        me->add_temp("apply/dodge",-j);
        me->add_temp("apply/attack", -j);
        me->start_busy(2+random(2));
        me->start_perform(2+random(2),"拳刀合一");
        return 1;
}



