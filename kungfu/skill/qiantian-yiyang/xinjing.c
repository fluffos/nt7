// jingxin.c 静

#include <ansi.h>

int exert(object me)
{
	int skill;
	skill = me->query_skill("literate", 1)/2;

	if(me->is_fighting())
	      return notify_fail("你正在战斗中，如何可以静下心来？\n");

	if((int)me->query_skill("qiantian-yiyang",1) < 100 )
	      return notify_fail("你的乾天一阳功不够娴熟，内力的冲撞使你静不下心来！\n");

	if(me->query("class") != "bonze" )
	      return notify_fail("你没有出家，内力的冲撞使你静不下心来！\n");

	if((int)me->query_skill("buddhism",1) < 50 )
	      return notify_fail("你的佛学修为不够，无法静下心来潜修！\n");

	if (me->query("neili") < 300  ) 
		return notify_fail("你的内力不够。\n");

	if (me->query_temp("dali_jing"))
		return notify_fail("你正在静心潜修。\n");
       
	me->add("neili", -250);

	message_vision(GRN "\n$N闭目盘膝坐下，只觉心中清静平和，渐渐进入忘我之境。\n" NOR, me);

	me->set_temp("dali_jing", me->query("int"));  
	me->add_temp("apply/intelligence", me->query("int"));

	call_out("remove_effect", 1, me, skill);
	return 1;
}

void remove_effect(object me, int d)
{
	int i;

	if (!me) return;
	if (me->query_skill_mapped("force") == "qiantian-yiyang"
	 && --d > 0) {
		call_out("remove_effect", 1, me, d);
		return;
	}
	i = me->query_temp("dali_jing");
	me->add_temp("apply/intelligence", -i);
	me->delete_temp("dali_jing");
	tell_object(me, HIY "你心中杂念又生，无法继续潜修了。\n" NOR);
}

string exert_name(){ return GRN"心经"NOR; }

int help(object me)
{
        write(GRN"\n乾天一阳功之「心经」："NOR"\n\n");
        write(@HELP
        要求：  当前内力 550 以上；
                乾天一阳功等级 100 以上；
                禅宗心法等级 50 以上；
                必须出家。

HELP
        );
        return 1;
}
