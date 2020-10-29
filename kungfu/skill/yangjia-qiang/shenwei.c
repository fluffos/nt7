//shenwei.c
//Created by Redhat@Sjmud 2009/4/7
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

string perform_name(){ return HIR"神威枪"NOR; }
int perform(object me, object target)
{
        object weapon;
        int skill,improve;

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("「神威枪」只能对战斗中的对手使用。\n");

        if( !objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "spear" )
                return notify_fail("你手中无枪，怎能运用「神威枪」？！\n");

        if( me->query_temp("yjq/shenwei"))
                return notify_fail("你正在使用「神威枪」绝技！\n");
                
        if( me->query_temp("yjq/qinghe"))
                return notify_fail("你正在使用「骤雨清荷」绝技！\n");
                
        if( me->query_temp("yjq/jifeng"))
                return notify_fail("你正在使用「疾风枪」绝技！\n");

        if((int)me->query_skill("yangjia-qiang", 1) < 250
         ||(int)me->query_skill("spear", 1) < 250)
                return notify_fail("你修为还不够，还未能领悟「神威枪」！\n");

        if (me->query_skill_mapped("spear") != "yangjia-qiang"
         || me->query_skill_mapped("parry") != "yangjia-qiang")
                return notify_fail("你现在无法使用「神威枪」进行攻击。\n");

        if( me->query("max_neili") <= 6000 )
                return notify_fail("你的内力修为不足，不足以施展「神威枪」！\n");

        if( me->query("neili") <= 3000 )
                return notify_fail("你的内力不够，不足以施展「神威枪」！\n");

        if( me->query("jingli") <= 2000 )
                return notify_fail("你的精力有限，不足以施展「神威枪」！\n");
                
        if( (int)me->query_str() < 25 )
		            return notify_fail("你的先天臂力不足，估计无法使出「神威枪」绝技。\n");

        message_vision(HIM"\n$N运筹帷幄，突然怒发冲冠使出杨家枪绝技之「神威枪」，只见"NOR+weapon->name()+HIM"环绕着红色光芒，宛如"HIR"火焰枪"HIM"一般！\n" NOR, me);

        if(userp(me)){
           me->add("neili", -300);
           me->add("jingli", -50);
        }
        skill = me->query_skill("spear");
      	improve = skill/4 + random(skill/4);
      	if ( improve > 100 ) improve = 100 + random(improve-100) / 5;

        me->set_temp("yjq/shenwei", improve);
        me->add_temp("apply/damage", improve);
        me->add_temp("apply/spear", improve);
        me->add_temp("apply/strength", improve/10 );
        call_out("remove_effect", 1,  me, weapon, skill);
        me->start_perform(5+random(8), "「神威枪」");
        return 1;
}

void remove_effect(object me,object weapon,int count)
{
        int i;
        if(!me) return;
        if(! me->is_fighting()
         || !weapon
         || me->query_skill_mapped("spear") != "yangjia-qiang"
         || me->query_skill_mapped("parry") != "yangjia-qiang"
         || count < 1 ){
          i = me->query_temp("yjq/shenwei");
          me->add_temp("apply/spear", -i);
          me->add_temp("apply/damage", -i);
          me->add_temp("apply/strength", -i/10 );
          me->delete_temp("yjq/shenwei");
	if (weapon)
		message_vision(HIW"\n$N一套「神威枪」使完，手中"NOR+weapon->name()+HIY"上的红色光芒逐渐消失了。\n"NOR, me);
          return;
        }
        else {
          me->start_perform(1,"「神威枪」");
          call_out("remove_effect", 1, me, weapon, count -1);
        }
}




