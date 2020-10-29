// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;
        string msg;
        mapping buff, data;

        if (target != me) 
                return notify_fail("你只能用混天气功来提升自己的战斗力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够。\n");
                
        if( BUFF_D->check_buff(me, "powerup") )
                return notify_fail("你已经在运用类似的武功了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        msg = HIR "$N微一凝神，运起混天气功，全身骨节发出一阵爆豆般的声响ⅵ\n" NOR;

        data =  ([
                        "attack" : skill/3,
                        "defense": skill/3,
                ]);
        buff =
                ([
                        "caster": me,
                        "target": me,
                        "type"  : "powerup",
                        "attr"  : "bless",
                        "name"  : "混天气功·战神",
                        "time"  : skill,
                        "buff_data": data,      
                        "buff_msg" : msg,
                        "disa_msg" : "你的混天气功运行完毕，将内力收回丹田。\n",
                        
                ]);
        BUFF_D->buffup(buff);

        if( me->is_fighting() ) 
                me->start_busy(3);

        return 1;
}