// jujing.c 聚精成气
// by augx@sj  6/11/2002

#include <ansi.h>

int exert(object me)
{
	int i;

	if ( me->query("tls"))
		return notify_fail("你已经出家了，怎么能用此种俗家武功！\n");

	if ( me->query("family/master_name") != "一灯大师" )
		return notify_fail("你非一灯弟子，经脉恐怕受不了怎么大的内力冲击。\n");

	if (me->query_skill("qiantian-yiyang",1) < 300 )
		return notify_fail("你的乾天一阳功不够娴熟，无法「聚精成气」。\n");

	if( me->query_skill_mapped("force") != "qiantian-yiyang" )
		return notify_fail("你所使用的内功不对。\n");

	if ( me->query_skill("yiyang-zhi", 1) < 300 )
		return notify_fail("你的一阳指等级不够，无法「聚精成气」。\n");

	if ( me->query_skill_mapped("finger") != "yiyang-zhi"
	|| me->query_skill_prepared("finger") != "yiyang-zhi") 
		return notify_fail("你必须结合一阳指使用「聚精成气」。\n");

	if (me->query("max_neili") < 6000  )
		return notify_fail("你的内劲修为不够。\n");

	if (me->query("neili") < 3000  )
		return notify_fail("你的内力不够。\n");

	if (me->query("max_jing") < 2000  )
		return notify_fail("你的精血不足。\n");

	if (me->query("jing") < 2000  )
		return notify_fail("你的精血不足。\n");

	if (me->query_temp("dali/jujing"))
		return notify_fail("你已经使用「聚精成气」了。\n");

	message_vision(HIY"\n$N凝神聚气，脸色数变，只感觉头脑一下子空白，肤色红润了许多。\n"NOR, me);

	i = me->query_skill("qiantian-yiyang",1);
	i = i * i / 60;
	i = MIN(i,me->query("jing")-100);
	i = MIN(i,me->query("neili"));

	me->add("neili", -i);
	me->add("max_jing",-i);
	me->add("eff_jing",-i);
	me->add("jing",-i);
	me->add("max_qi",i);
	me->add("eff_qi",i);
	me->add("qi",i);
	if (me->query_skill("qiantian-yiyang",1)>449)
	{     
       me->set_temp("apply/attack",me->query_skill("qiantian-yiyang",1)/5);
	 if (me->query("tls/yideng/ronghe")=="pass")
	  {message_vision(HIC"\n$N瞬间领悟到一灯大师所提到的「先天功」的奥义，手上的力道明显增强了不少。\n"NOR, me);
	   me->set_temp("apply/damage",me->query_skill("qiantian-yiyang",1)/5);}
	 else
	   me->set_temp("apply/damage",me->query_skill("qiantian-yiyang",1)/10);
	
	}
   
	me->set_temp("dali/jujing", i);
	me->set("dali/jujing", i);
	me->set_temp("dali/jujing1", 0);
	if (me->query_skill("qiantian-yiyang",1)<449)
	{
	 if( me->is_fighting() ) me->start_busy(random(2));
	 me->start_exert(3, "聚精成气");
	}
		

	call_out("remove_effect", 6, me, 3+me->query_skill("qiantian-yiyang", 1)/50);
	return 1;
}

void remove_effect(object me, int tick)
{
	int i;

	if(!me) return;
	if( me->query_skill_mapped("force")!="qiantian-yiyang" || !tick ) {
		tell_object(me, HIY"\n时间一长，你感觉支持不住，精神开始分散了。\n" NOR);
		i = me->query_temp("dali/jujing");
		me->delete_temp("dali/jujing");
		me->delete("dali/jujing");
		me->delete_temp("dali/jujing1");
        if (me->query_skill("qiantian-yiyang",1)>449)
	    {
		   me->set_temp("apply/attack",-me->query_skill("qiantian-yiyang",1)/5);
	     if (me->query("tls/yideng/ronghe")=="pass")
		   me->set_temp("apply/damage",-me->query_skill("qiantian-yiyang",1)/5);
	     else
	       me->set_temp("apply/damage",-me->query_skill("qiantian-yiyang",1)/10);
		 }
		me->add("max_jing",i);
		me->add("eff_jing",i);
		if( me->query("jing") > me->query("eff_jing") )
			me->set("jing",me->query("eff_jing"));

		me->add("max_qi",-i);
		if( me->query("eff_qi") > me->query("max_qi") )
			me->set("eff_qi",me->query("max_qi"));
		if( me->query("qi") > me->query("eff_qi") )
			me->set("qi",me->query("eff_qi"));
		return;
	}
	call_out("remove_effect", 6, me, tick-1);
}

string exert_name(){ return HIY"聚精成气"NOR; }

int help(object me)
{
	write(HIY"\n乾天一阳功之「聚精成气」："NOR"\n\n");
        write(@HELP
	聚精成气是一灯大师从王重阳所授之先天功道家武学中参悟出来的，
	因此只传授给俗家弟子。

	要求：	当前内力 550 以上；
		乾天一阳功等级 300 以上；
		一阳指等级 300 以上；
		激发指法为一阳指，备指法为一阳指；
		必须为俗家弟子,且拜师一灯。450级后有飞跃,增加命中和伤害。

HELP
        );
        return 1;
}
