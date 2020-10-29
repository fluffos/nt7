// This program is a part of NT MudLIB
// shield.c 九阳护体神功

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;

        if (target != me)
                return notify_fail("你只能用九阳神功来提升自己的防御力。\n");

        if ((int)query("neili", me) < 100)
                return notify_fail("你的真气不够。\n");

        if ((int)me->query_skill("jiuyang-shengong", 1) < 40)
                return notify_fail("你的九阳神功等级不够。\n");

        if( BUFF_D->check_buff(me, "shield") )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        msg = HIR "$N" HIR "默念九阳神功的口诀：他"
                            "强由他强，清风拂山冈。他横任他横，"
                            "明月照大江……\n刹那间只见$N"
                        HIR "全身顿时浮现出一层刚猛的劲气，将$P"
                        HIR "全全笼罩。\n" NOR;

        data = ([
                "armor" : skill,
                "defense" : skill,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "shield",
                "attr"  : "bless",
                "name"  : "九阳神功·护体神功",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的九阳神功运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}
