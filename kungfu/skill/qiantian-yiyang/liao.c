//COOL@SJ 200001009 add yyz liao yyz_hurt
#include <ansi.h>

string exert_name() {return HIY"纯阳疗伤"NOR;}

int exert(object me, object target)
{
	if( !objectp(target) )
		return notify_fail("你要用一阳指为谁疗伤？\n");

	if (target->is_corpse() || !target->is_character())
		return notify_fail("那不是活物耶！\n");

	if (target->is_busy())
		return notify_fail("对方现在没有空接受你的疗伤。\n");

	if((int)me->query_skill("force") < 270 )
	      return notify_fail("你的乾天一阳功不够娴熟，无法替人疗伤！\n");

	if((int)me->query_skill("yiyang-zhi",1) < 180 )
	      return notify_fail("你的一阳指神功不够娴熟，无法替人疗伤！\n");

	if (me->query_skill_prepared("finger") != "yiyang-zhi"
	|| me->query_skill_mapped("finger") != "yiyang-zhi")
		return notify_fail("你现在无法使用一阳指替人疗伤！\n");

	if( me->is_fighting() && target != me)
		return notify_fail("战斗中无法替别人疗伤！\n");

        if( target->is_fighting()&&target != me)
                return notify_fail("对方正在战斗，无法替他疗伤！\n");

	if( (int)me->query("max_neili") < 2000 )
		return notify_fail("你的内力修为不够。\n");

	if( (int)me->query("neili") < 400 )
		return notify_fail("你的真气不够。\n");

	if((int)me->query_skill("medicine", 1) < 120 )
	       return notify_fail("看样子你的医理知识所知甚少，不知如何下手? \n");

	if (!target->query_condition("yyz_hurt")
	&& target->query("eff_qi") >= target->query("max_qi"))
		return notify_fail( target->name() + "并没有受伤！\n");

	if (me->is_fighting()) {
		message_vision(
			HIY"\n$N手臂颤动，犹如蜻蜓点水，一口气连点过自己胸口的十二道大穴，纯阳真气不断透入……\n\n"
			HIM"只这片刻之间，$N脸色便有了红晕，伤势好多了。\n" NOR, me);
		if (target->query_condition("yyz_hurt")) target->clear_condition("yyz_hurt");
		if ((int)target->query("eff_qi") < (int)target->query("max_qi"))
		{
			me->add("neili",-me->query_skill("force")/3);
			me->receive_curing("qi", 10 + me->query_skill("force") );
			me->receive_heal("qi", 10 + me->query_skill("force"));
		}
		me->start_exert(5, "疗伤");
	} else {
		target->start_busy(2);
	  	if (target != me){
			me->start_busy(2);
	    		message_vision(HIY"\n$N伸出右手食指，微一凝气，听得嗤嗤声响, 食指沿任、督二脉各穴依此点过，最后按在$n胸口的膻中大穴上，纯阳内力源源透入。。。\n\n"
			   	HIM"\n$N头顶冒起丝丝白气，$n感觉一股温正平和的内力在体内循环流动，过了一盏茶时分，$N才放开手指。只这片刻之间，$n双颊\n"
			   	HIM"便有了红晕，脸色看起来也好多了。\n" NOR,me,target);
		}
		else
	   		message_vision(HIY"\n$N盘腿坐下，微一凝气，食指依任、督二脉各穴依此点过，食指一收，虚掌按在胸口膻中大穴，纯阳真气源源透入。。。\n\n"
				HIM"$N头顶冒起丝丝白气，过了一盏茶时分，才放开手指,$N的脸色看起来也好多了。\n" NOR,me);
	   	if( (target != me)
	    	&& userp(target)
	    	&& target->query("eff_qi") < target->query("max_qi")/5) {
	     		if (!random(4)) me->add("max_neili",-1);
	     		me->add("yyz_cure",1);
		}
		if (target->query_condition("yyz_hurt")) target->clear_condition("yyz_hurt");
		if (target->query("eff_qi") < target->query("max_qi"))
		{
		   	me->add("neili", -me->query_skill("force")/4);
	   		target->receive_curing("qi", 10 + me->query_skill("force"));
	   		target->receive_heal("qi", 10 + me->query_skill("force"));
	   		me->start_busy(3);
	   		target->start_busy(3);
	 	}
	}
	return 1;
}
