// This program is a part of NITAN MudLIB
// shield.c 八荒六合唯我独尊之护体神功

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;
        string msg;
        mapping buff, data;

        if( target != me )
                return notify_fail("你只能用八荒六合唯我独尊来提升自己的防御力。\n");

        if( BUFF_D->check_buff(me,"shield") )
                return notify_fail("你正在施展八荒六合唯我独尊神功。\n");
                
        if( query("neili", me) < 100 )
                return notify_fail("你的内力不够。\n");

        if( (int)me->query_skill("bahuang-gong", 1) < 50 )
                return notify_fail("你的八荒六合唯我独尊修为不够。\n");
        
        skill = me->query_skill("force");
        addn("neili", -100, me);

        
        msg = HIW "$N" HIW "身子一晃，衣袖一波波的不住激荡，劲气逼人！\n" NOR;

        data =  ([
	                "armor" : skill/2,
	        ]);
	        
        buff =
                ([
			"caster": me,
			"target": me,
			"type"  : "shield",
			"attr"  : "bless",
			"name"  : "八荒六合功·护体神功",
			"time"  : skill,
			"buff_data": data,	
			"buff_msg" : msg,
			"disa_msg" : "你的八荒六合护体神功运行完毕，将内力收回丹田。\n",
                ]);

        BUFF_D->buffup(buff);

        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}
