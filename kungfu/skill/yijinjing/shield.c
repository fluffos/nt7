// This program is a part of NT MudLIB
// shield.c 

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;
        string msg;
        mapping buff, data;

        if( query("family/family_name", me) != "少林派" && !query("yuanshen", me) )
                return notify_fail("你不是少林弟子，无法使用易筋经绝技。\n");

        if( target != me )
                return notify_fail("你只能用易筋经来激发金刚不坏体 \n");

        if( query("neili", me)<100 )
                return notify_fail("你的真气不够。\n");

        if( (int)me->query_skill("yijinjing", 1) < 40 )
                return notify_fail("你的易筋经等级不够。\n");

        if( BUFF_D->check_buff(me, "shield") )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        msg = HIY "$N" HIY "双目突然精芒暴涨,身上蓦地涌起" HIY "一股凛冽金光。\n" NOR;

        data =  
        ([
	        "armor" : skill,
        ]);
	       
        buff =
        ([
                "caster": me,
                "target": me,
	        "type"  : "shield",
	        "attr"  : "bless",
	        "name"  : "易筋经·护体神功",
	        "time"  : skill,
	        "buff_data": data,	
	        "buff_msg" : msg,
	        "disa_msg" : "你的易筋经运行完毕，金光隐隐退去，你恢复原来的样子。\n",
        ]);

        BUFF_D->buffup(buff);

        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}
