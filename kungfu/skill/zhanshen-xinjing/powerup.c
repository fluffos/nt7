// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;
 
        if( target != me ) 
                return notify_fail("你只能用战神心经来提升自己的战斗力。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的内力不够。\n");
        if( BUFF_D->check_buff(me, "powerup") ) 
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);

        msg = HIR "$N凝神息气，运起战神心经，只见一股轻烟缭绕周身。\n" NOR;

        data = ([
                "attack" : skill*2/3,
                "defense": skill*2/3,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "战神心经·战神",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的战神心经运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}
