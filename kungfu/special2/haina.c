
#include <ansi.h>
#include <combat.h>

int is_scborn() { return 1; }

string name() { return HIC "海纳百川" NOR; }

int perform(object me, string skill, string arg)
{
        int joblv, armor, damage, attack;

	joblv = me->query_joblv();

        if (me->query_temp("special2/haina/joblv"))
                return notify_fail("你已经在运功中了。\n");

	if (me->query("yhjob/job") != "隐士")
		return notify_fail("你的职业错误，无法施展。\n");
		
	if (me->query("neili") < 1000)
		return notify_fail("你的内力不足，无法施展。\n");

	if (joblv < 20)
		return notify_fail("你的职业等级不足，无法施展。\n");		

        if (me->is_busy())return notify_fail("等你忙完再说吧！\n");

        message_vision(HIM "$N" HIM "脸色微变，深吸一口气，然后缓缓吐出，顷刻间，周身弥漫着阵阵薄雾。\n" NOR, me);
 
        me->add("neili", -1000);
        me->start_busy(1);

	joblv = joblv + me->query("lhpoint/special/haina") * 7;

        me->set_temp("special2/haina/joblv", joblv);
	armor = me->query_temp("apply/armor");
	damage = me->query_temp("apply/damage");
	attack = 1;//me->query_temp("apply/attack"); 在 combatd.c里做处理

	armor = armor + armor / 10;
	attack = 1;//attack * (10 + (joblv - 20) / 2) / 100;
	damage = damage + damage / 10;
	if (damage <= 0)damage = 0;
	me->add_temp("apply/armor", armor);
	me->add_temp("apply/damage", damage);
	me->add_temp("apply/attack", attack);

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, joblv, armor, damage, attack :), joblv * 10);	
	
        return 1;
}

void remove_effect(object me, int joblv, int armor, int damage, int attack)
{
	if (! objectp(me))return;
	
        if ((int)me->query_temp("special2/haina/joblv"))
        {			
		me->add_temp("apply/armor", -1 * armor);
		me->add_temp("apply/damage", -1 * damage);
		me->add_temp("apply/attack", -1 * attack);
	        me->delete_temp("special2/haina/joblv");
	        tell_object(me, "你海纳百川运功完毕。\n");
        }
}

