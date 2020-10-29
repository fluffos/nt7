//  lihua.c 疾风枪 
//Created by Redhat@Sjmud 2009/4/7

#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return MAG"疾风枪"NOR;}

private int remove_effect(object me, int amount);

int perform(object me)
{
        object weapon = me->query_temp("weapon");  
        int skill;
    
        if(!me->is_fighting() )
                return notify_fail("「疾风枪」只能在战斗中使用。\n");
    
        if ((int)me->query_skill("yangjia-qiang", 1) < 350 )
                return notify_fail("你的杨家枪不够娴熟，不能真正发挥「疾风枪」的威力。\n");
    
        if((int)me->query_skill("spear", 1) < 350 )
                return notify_fail("你的基本内功等级不够，不能使用「疾风枪」。\n");

        if( !objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "spear" )
                return notify_fail("你手中无枪，怎能运用「疾风枪」？！\n");
                                
        if (me->query_skill_mapped("spear") != "yangjia-qiang"
         || me->query_skill_mapped("parry") != "yangjia-qiang")
                return notify_fail("你现在无法使用「神威枪」进行攻击。\n");
    
        if ((int)me->query("max_neili") < 6000 )
                return notify_fail("你的内力修为太低，不能使用「疾风枪」。\n");

        if ((int)me->query("neili") < 3000 )
                return notify_fail("你现在内力太弱，不能使用「疾风枪」。\n");

        if ((int)me->query("jingli") < 2000 )
                return notify_fail("你现在精力太少，不能使用「疾风枪」。\n");

        if(me->query_temp("yjq/jifeng"))
                return notify_fail("你现正在使用「疾风枪」。\n");

        if(me->query_temp("yjq/shenwei"))
                return notify_fail("你现正在使用「神威枪」。\n");
                
        if(me->query_temp("yjq/qinghe"))
                return notify_fail("你现正在使用「骤雨清荷」。\n");

    message_vision(HIC"$N融合贯通武学，使出杨家枪绝技之「"MAG"疾风枪"HIC"」，只见"+weapon->query("name")+HIC"招数凌厉，招数犹如幻影般朝发夕至！\n"NOR, me);
        me->start_exert(2+random(2),"「疾风枪」");
        me->add("neili", -500);
        me->add("jingli", -300);
        me->start_busy(1+random(2));
    
        skill = me->query_skill("yangjia-qiang", 1);
        skill = skill /3;
        me->add_temp("apply/attack",  skill);
        me->set_temp("double_attack",1);
        me->set_temp("yjq/jifeng", skill);

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
       i = me->query_temp("yjq/jifeng");
           me->add_temp("apply/attack", -i);
           me->delete_temp("double_attack");
           me->delete_temp("yjq/jifeng");
           if(living(me) && !me->is_ghost())
              message_vision(HIW"$N一套「疾风枪」使完，脸上不由凸现一股豪气。\n"NOR, me);
           return;
        } 
        call_out("check_fight", 1, me, weapon);
}

int help(object me)
{
   write(YEL"\n杨家枪「"HIG"疾风枪"YEL"」："NOR"\n");
   write(@HELP
   指令：perform jifeng
   
   大幅提高攻击速度。

   要求：杨家枪350级，
         基本枪法350级，
         最大内力 5000 以上，
         当前内力 3000 以上，
         当前精力 2000 以上，
         激发杨家枪为招架。
HELP
   );
   return 1;
}
