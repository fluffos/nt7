// This program is a part of NT MudLIB

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;
        
        if( target != me )
                return notify_fail("你只能用太极神功来提升自己的防御力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真气不够。\n");

        if( (int)me->query_skill("taiji-shengong", 1) < 40 )
                return notify_fail("你的太极神功等级不够。\n");

        if( BUFF_D->check_buff(me, "shield") )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        msg = HIR "$N" HIR "默念太极神功的口诀：他"
                            "强由他强，清风拂山冈。他横任他横，"
                            "明月照大江……\n刹那间只见$N" 
                        HIR "全身顿时浮现出一层刚猛的劲气，将$P"
                        HIR "全全笼罩。\n" NOR;

        data = ([
                "armor": skill/2,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "shield",
                "attr"  : "bless",
                "name"  : "太极神功·护体神功",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的太极神功运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if (me->is_fighting()) me->start_busy(2);

        return 1;
}
