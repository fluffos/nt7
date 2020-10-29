// pi.c 打狗枪法--闪击
//Created by Redhat@Sjmud 2009/4/7

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return RED"闪击"NOR; }
int perform(object me, object target)
{
	string msg;
	int extra;
	object weapon;
	if(me->is_busy())
		return notify_fail("你现在没空！！\n");
        if( (int)me->query_skill("yangjia-qiang",1) < 50)
        return notify_fail("你目前功力还使不出「闪击」。\n");
    	if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "spear")
			return notify_fail("你使用的武器不对。\n");
	if( (int)me->query("neili") < 500 )
    return notify_fail("你的内力不够。\n");
	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("［闪击］只能对战斗中的对手使用。\n");
	weapon = me->query_temp("weapon");
	extra = me->query_skill("yangjia-qiang",1) *2 ;
	me->add_temp("apply/attack", extra);	
	me->add_temp("apply/damage", extra);
	msg = RED  "$N手中的"+ weapon->name() +"幻出一环枪影，"+weapon->name() +"划破长空，向$n疯狂划去！" NOR;
	COMBAT_D->do_attack(me,target, weapon, TYPE_REGULAR,msg);
	me->add_temp("apply/attack", -extra);
	me->add_temp("apply/damage", -extra);
 me->start_perform(3+random(2), "「闪击」");

	me->start_busy(2);
	return 1;
}

int help(object me)
{
   write(YEL"\n杨家枪「"HIG"闪击"YEL"」："NOR"\n");
   write(@HELP
   指令：perform shanji

   要求：杨家枪50级，
         基本枪法50级，
         当前内力 500 以上，
         当前精力 100 以上，
HELP
   );
   return 1;
}
