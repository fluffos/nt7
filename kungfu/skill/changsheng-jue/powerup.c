#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;

        if (target != me)
                return notify_fail("你只能用长生决来提升自己的战斗力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够。\n");

        if( BUFF_D->check_buff(me, "powerup") )
                return notify_fail("你已经在运用类似的武功了。\n");
                
        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        msg = HIW "$N" HIW "微一凝神，运起长生决，将真气"
                        "凝聚在丹田之中，沿奇经八脉遍布全身！\n" NOR;
        
        data = ([
                "attack" : skill*2/5,
                "defense": skill*2/5,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "长生决·战神",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的长生决运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}
