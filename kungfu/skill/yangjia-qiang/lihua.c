//  lihua.c 暴雨梨花 
//Created by Redhat@Sjmud 2009/4/7

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

 string perform_name(){ return HIG"暴雨梨花"NOR; }
int perform(object me, object target)
{
        object weapon, ob;
        int speed, attack, lv, damage;

        lv = (int)me->query_skill("yangjia-qiang", 1); 
        damage = lv + random(lv/2) + (int)me->query_skill("spear",1);
                      attack = lv + random(lv/2);
                         speed = me->query_skill("spear")/80;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
	               return notify_fail("「暴雨梨花」只能对战斗中的对手使用。\n");

        if( me->query_temp("yjq/lihua"))
	               return notify_fail("你正在使用「暴雨梨花」！\n");
	               
	      if( me->query_temp("lihua"))
	               return notify_fail("你刚使用过「暴雨梨花」，再调整下内息吧！\n");

        if (!objectp(weapon = me->query_temp("weapon")) 
          || weapon->query("skill_type") != "spear"
          || me->query_skill_mapped("spear") != "yangjia-qiang"
          || me->query_skill_mapped("parry") != "yangjia-qiang")
                 return notify_fail("你手里无枪，如何使用「暴雨梨花」？\n");
                 
        if((int)me->query("max_neili") < 15000 )
               return notify_fail("你的内力修为不够，无法使用「暴雨梨花」！\n");

        if( (int)me->query("neili") < 10000 )
	             return notify_fail("你的内力不够！\n");

        if( me->query_skill("yangjia-qiang", 1) < 450 )
	              return notify_fail("你的「杨家枪」等级不够，无法使用「暴雨梨花」！\n");
	               
        if( me->query_skill("spear", 1) < 400 )
                return notify_fail("你的「基本枪法」等级不够，无法使用「暴雨梨花」！\n");
                 
        if( (int)me->query_con() < 22 )
		            return notify_fail("你的先天根骨不足，「暴雨梨花」绝技对你来说几乎是太难了。\n");

        message_vision(HIC "\n$N突感浑身气力充沛力道无比，将"+weapon->query("name")+HIC"后柄突然举高握于手心，猛然向$n胸口如暴风骤雨般突刺\n"+
                            "只见"+weapon->query("name")+HIC"枪锋到处突显出宛如"HIG"暴雨梨花"HIC"般气旋，其枪锋势不可当,使人目不暇接，堪当杨家枪之绝旨！"NOR"\n" NOR, me,target);
        me->start_perform(3+random(5), "「暴雨梨花」");
        ob = me->select_opponent();
        me->set_temp("lihua",4);
        me->set_temp("yjq/lihua");
        call_out("checking", 1, me, target);
        return 1;
}

  void checking(object me, object target, int speed, int damage, int attack)
{

        object weapon;
	      if ( !objectp( me ) ) return;
        weapon = me->query_temp("weapon");

        if (!objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "spear") {
		       tell_object(me, "\n你手中无枪，当下停止了暴雨梨花的架势。\n" NOR);
		       me->delete_temp("lihua");
		       me->delete_temp("yjq/lihua");
		       return;
	}

        if ( me->query_temp("lihua") ==4)
      message_vision(HIM"\n只见"+weapon->name()+HIM"陡然迸发，枪锋气旋直刺$n，「"HIG"暴雨梨花"HIM"」果然天下闻名，速度快的迅无绝伦，无人可挡！\n" NOR, me,target);
	{
		me->add_temp("apply/attack",  (int)me->query_skill("yangjia-qiang", 1)/2);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		    me->add_temp("apply/attack", -(int)me->query_skill("yangjia-qiang", 1)/2);
		 me->add("neili", -500);
		 me->start_busy(1);
		target->start_busy(1+random(1));
		}
		
		if ( me->query_temp("lihua") ==4 )
	    message_vision(HIB"\n忽然一道绚彩蓝色光线延着"+weapon->name()+HIB"向枪尖疾去，$N大声喝道：「"+target->name()+HIB"，小心！」\n" NOR, me,target);
           damage = (int)me->query_skill("yangjia-qiang", 1)+ (int)me->query_skill("spear", 1);
           damage = random(damage)*2 + random(damage);
        {       
    me->start_busy(1+random(2));      	  
		target->start_busy(1+random(1));
		me->add_temp("apply/attack",  (int)me->query_skill("yangjia-qiang", 1)/2);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),2);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		   me->add_temp("apply/attack", -(int)me->query_skill("yangjia-qiang", 1)/2);
		target->add("neili", -damage/10);
		   me->add("neili", -400);    
       message_vision(RED"\n$n只觉身体一凉，"+weapon->name()+RED"已经自$N胸口对穿过去，鲜血蹦的满地！\n"NOR,me,target);
        }		
	
    if ( me->query_temp("lihua") !=3 )
    	message_vision(WHT"\n$N将全身内力贯穿于"+weapon->name()+WHT"只见刚才还是如暴雨梨花般的突刺，又猛然转换招式杨家枪之"HIY"「回马枪」"WHT"绝技！\n" NOR, me,target);
    {        
    me->add("neili", -500);
    me->add("jingli",-500);
    me->set_temp("yjq/huima",1);

    me->add_temp("apply/attack",  (int)me->query_skill("yangjia-qiang", 1) /3 );
    me->add_temp("apply/damage", (int)me->query_skill("yangjia-qiang",1) /3 );
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    me->add_temp("apply/damage", -(int)me->query_skill("yangjia-qiang",1) /3 );
    me->add_temp("apply/attack",   -(int)me->query_skill("yangjia-qiang", 1) /3 );
    
    me->delete_temp("yjq/huima");
    me->start_busy(1+random(1));
    me->delete_temp("yjq/lihua");
      call_out("lihua_finish", 6+random(4), me);
		}
	        
	      	    
 }
 
void lihua_finish(object me,object target)
{
        object weapon;
	      if ( !objectp( me ) )
		       return;
        weapon = me->query_temp("weapon");
       message_vision(HIG"\n$N一套「暴雨梨花」使完，"+weapon->name()+HIG"速度渐渐慢了下来。\n"NOR, me);
        me->delete_temp("lihua");
        me->start_busy(2);     
}

int help(object me)
{
   write(YEL"\n杨家枪「"HIG"暴雨梨花"YEL"」："NOR"\n");
   write(@HELP
   指令：perform lihua

   要求：杨家枪450级，
         基本枪法450级，
         最大内力 15000 以上，
         当前内力 10000 以上，
         当前精力 6000 以上，
         激发杨家枪为招架。
HELP
   );
   return 1;
}