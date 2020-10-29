//  lihua.c 骤雨清荷 
//Created by Redhat@Sjmud 2009/4/7

#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return HIC"骤雨清荷"NOR;}

private int remove_effect(object me, int amount);

int perform(object me)
{
        object weapon = me->query_temp("weapon");  
        int skill;
    
        if(!me->is_fighting() )
                return notify_fail("「骤雨清荷」只能在战斗中使用。\n");
    
        if ((int)me->query_skill("yangjia-qiang", 1) < 150 )
                return notify_fail("你的杨家枪不够娴熟，不能真正发挥「骤雨清荷」的威力。\n");
    
        if((int)me->query_skill("spear", 1) < 150 )
                return notify_fail("你的基本内功等级不够，不能使用「骤雨清荷」。\n");

        if( !objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "spear" )
                return notify_fail("你手中无枪，怎能运用「骤雨清荷」？！\n");
                                
        if (me->query_skill_mapped("spear") != "yangjia-qiang"
         || me->query_skill_mapped("parry") != "yangjia-qiang")
                return notify_fail("你现在无法使用「神威枪」进行攻击。\n");
    
        if ((int)me->query("max_neili") < 2500 )
                return notify_fail("你的内力修为太低，不能使用「骤雨清荷」。\n");

        if ((int)me->query("neili") < 1000 )
                return notify_fail("你现在内力太弱，不能使用「骤雨清荷」。\n");

        if ((int)me->query("jingli") < 500 )
                return notify_fail("你现在精力太少，不能使用「骤雨清荷」。\n");

        if(me->query_temp("yjq/qinghe"))
                return notify_fail("你现正在使用「骤雨清荷」。\n");

        if(me->query_temp("yjq/shenwei"))
                return notify_fail("你现正在使用「神威枪」。\n");
                
        if(me->query_temp("yjq/jifeng"))
                return notify_fail("你现正在使用「疾风枪」。\n");

    message_vision(HIM"$N使出杨家枪绝技之「"HIG"骤雨清荷"HIM"」，只见"+weapon->query("name")+HIM"只觉感觉身体轻盈飘逸，潇洒无比！\n"NOR, me);
        me->start_exert(5+random(2),"「骤雨清荷」");
        me->add("neili", -200);
        me->add("jingli", -500);
        me->start_busy(1+random(2));
    
        skill = me->query_skill("yangjia-qiang", 1);
        me->add_temp("apply/attack",  -skill/5);
        me->add_temp("apply/damage",  -skill/5);
        me->add_temp("apply/parry",  skill/2);
        me->add_temp("apply/dodge",  skill/2);
        me->set_temp("yjq/qinghe", skill);

        call_out("check_fight", 1, me, weapon);
        return 1;
}

void check_fight(object me, object weapon)
{  
        object wep;
        int i;

        if (!me) return;
        wep = me->query_temp("weapon");  
        if( !me->is_fighting()
         || !living(me)
         || me->is_ghost()
         || me->query_skill_mapped("spear") != "yangjia-qiang" 
         || me->query_skill_mapped("parry") != "yangjia-qiang" 
         || !wep
         || weapon != wep ){
       i = me->query_temp("yjq/qinghe");
        me->add_temp("apply/attack", i/5);
        me->add_temp("apply/damage", i/5);
        me->add_temp("apply/parry",  -i/2);
        me->add_temp("apply/dodge",  -i/2);
           me->delete_temp("yjq/qinghe");
           if(living(me) && !me->is_ghost())
              message_vision(HIW"$N一套「骤雨清荷」使完，感觉到从没有过的飘逸。\n"NOR, me);
           return;
        } 
        call_out("check_fight", 1, me, weapon);
}

int help(object me)
{
   write(YEL"\n杨家枪「"HIG"骤雨清荷"YEL"」："NOR"\n");
   write(@HELP
   指令：perform qinghe

   要求：杨家枪150级，
         基本枪法150级，
         最大内力 2500 以上，
         当前内力 2000 以上，
         当前精力 500 以上，
         激发杨家枪为招架。
HELP
   );
   return 1;
}
