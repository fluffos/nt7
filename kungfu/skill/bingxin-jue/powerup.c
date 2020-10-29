// powerup.c 

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;
        mapping buff, data;
        string msg;
        
        if (target != me)
                return notify_fail("你只能用冰心决来提升自己的战斗力。\n");
                
        if( query("neili", me)<300 )
                return notify_fail("你的内力不够。\n");
                
        if( BUFF_D->check_buff(me,"powerup") )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -200, me);
        me->receive_damage("qi", 0);
        
        msg = HIW "$N" HIW "默运冰心决，全身关节一阵爆响，一股至阴的内劲从浑身经脉迸发出来。\n" NOR;
        
        data = ([
                "attack" : skill/3,
                "defense": skill/3,
        ]);
               
        buff = ([
	        "caster": me,
	        "target": me,
	        "type"  : "powerup",
	        "attr"  : "bless",
	        "name"  : "冰心决·战神",
	        "time"  : skill,
	        "buff_data": data,	
	        "buff_msg" : msg,
	        "disa_msg" : "你的冰心决运行完毕，将内力收回丹田。\n",
        ]);

        BUFF_D->buffup(buff);

        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}
