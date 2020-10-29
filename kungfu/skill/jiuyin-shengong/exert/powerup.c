// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
	int skill;
	int sk_fxj; // 飞絮劲的效果

	if (target != me)
		return notify_fail("你只能用九阴神功提升自己的战斗力。\n");

	if( query("neili", me)<100 )
		return notify_fail("你的内力不够!");

	if( query_temp("powerup", me) )
		return notify_fail("你已经在运功中了。\n");

	skill = me->query_skill("force");
	
	sk_fxj = me->query_skill("feixu-jin", 1);
	
	if (sk_fxj >= 200)
	{
		skill = skill + skill / 5;
	}
	else if (sk_fxj >= 300)
	{
		skill = skill + skill * 2 / 5;
	}
	else if (sk_fxj >= 500)
	{
		skill = skill + skill * 3 / 5;
	}
	
addn("neili", -100, 	me);
	me->receive_damage("qi", 0);

	message_combatd(HIY "$N" HIY "缓缓的吐出了一口气，只"
                        "见衣袖飘飘、气涨如鼓，似要飞扬！\n" NOR, me);

addn_temp("apply/attack", skill*2/5, 	me);
addn_temp("apply/defense", skill*2/5, 	me);
addn_temp("apply/damage", skill/3, 	me);
	
set_temp("powerup", 1, 	me);

	me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, skill:), skill);

	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
addn_temp("apply/attack", -1*amount*2/5, 	me);
addn_temp("apply/defense", -1*amount*2/5, 	me);
addn_temp("apply/damage", -1*amount/3, 	me);
	        
delete_temp("powerup", 	me);
                tell_object(me, "你的九阴神功运行完毕，将内力收回丹田。\n");
        }
}
