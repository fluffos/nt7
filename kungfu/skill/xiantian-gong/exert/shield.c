// shield.c 先天无极劲

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;

        if ((int)me->query_skill("xiantian-gong", 1) < 50)
                return notify_fail("你的先天功还不够深厚。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在的真气不够。\n");

        if( BUFF_D->check_buff(me, "shield") )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        msg = HIW "$N" HIW "深深吸了一口气，双臂一振，一股浑厚的气劲登"
              "时盘旋在身边四周。\n" NOR;     

        data = ([
                "armor" : skill/2,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "shield",
                "attr"  : "bless",
                "name"  : "先天功·护体神功",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的先天功运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);

        addn("neili", -100, me);
        if (me->is_fighting()) me->start_busy(2);

        return 1;
}
