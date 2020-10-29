#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;
        mapping buff, data;
        string msg;

        if (target != me)
                return notify_fail("你只能用碧云心法来提升自己的战斗力。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的内力不够。\n");

        if( BUFF_D->check_buff(me,"powerup") )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force", 1);
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        msg = HIR "$N凝神息气，运起碧云心法的最高境界，只见一股轻烟缭绕周身。\n" NOR;
        
        data = ([
                "attack" : skill/3,
                "defense": skill/3,
        ]);
        
        buff = ([
	        "caster": me,
	        "target": me,
	        "type"  : "powerup",
	        "attr"  : "bless",
	        "name"  : "碧云心法·战神",
	        "time"  : skill,
	        "buff_data": data,	
	        "buff_msg" : msg,
	        "disa_msg" : "你的碧云心法运行完毕，将内力收回丹田。\n",
        ]);

        BUFF_D->buffup(buff);

        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}
