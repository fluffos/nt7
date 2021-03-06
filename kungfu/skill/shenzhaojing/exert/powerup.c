// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;

        if (target != me)
                return notify_fail("你只能用神照经神功提升自己的战斗力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够!");

        if( BUFF_D->check_buff(me, "powerup") ) 
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        msg = HIC "$N" HIC "大喝一声，一股气浪登时如波"
                        "涛一般散布开来，直吹得四周飞沙走石！\n" NOR;

        data = ([
                "attack" : skill/3,
                "defense": skill/3,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "神照经神功·战神",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的神照经神功运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}
