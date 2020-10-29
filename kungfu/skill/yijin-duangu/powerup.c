// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;

        if (target != me)
                return notify_fail("你只能用易筋锻骨内功提升自己的战斗力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真气不够！");

        if( BUFF_D->check_buff(me, "powerup") )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        msg = HIW "$N暗自凝神，提运九阴真气，全身渐渐升起一层白雾。\n" NOR;

        data = ([
                "attack": skill/2,
                "defense":skill/2,
        ]);
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "易筋锻骨·战神",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的易筋锻骨运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}
