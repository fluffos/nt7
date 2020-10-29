// This program is a part of NT MudLIB
// Written by Lonely@nitan.org

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;
        string msg;
        mapping buff, data;
 
        if( target != me ) 
                return notify_fail("你只能用八荒六合功来提升自己的战斗力。\n");

        if( BUFF_D->check_buff(me, "powerup") )
                return notify_fail("你已经在运用类似的武功了。\n");
                
        if( query("neili", me) < 200 )
                return notify_fail("你的内力不够。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);

        msg = HIR "$N" HIR "凝神息气，运起八荒六合唯我独尊功，只见一股轻烟悄然缭绕周身。\n" NOR;
        
        data =  ([
                        "attack" : skill/2,
                        "defense": skill/3,
                ]);
        buff =
                ([
                        "caster": me,
                        "target": me,
                        "type"  : "powerup",
                        "attr"  : "bless",
                        "name"  : "八荒六合功·战神",
                        "time"  : skill,
                        "buff_data": data,      
                        "buff_msg" : msg,
                        "disa_msg" : "你的八荒六合唯我独尊功运行完毕，将内力收回丹田。\n",
                        
                ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}
