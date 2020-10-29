// powerup.c 龙相功加力

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;

        if( target != me )
                return notify_fail("你只能提升自己的战斗力。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够。\n");

        if( BUFF_D->check_buff(me, "powerup") )
                return notify_fail("你已经在运用类似的武功了。\n");

        skill = me->query_skill("force");

        msg = HIR "$N" HIR "大喝一声，全身骨骼节节暴响，一股"
                       "迅猛的罡气向四周扩散开来！\n" NOR;

        data = ([
                "attack" : skill/3,
                "defense": skill/3,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "龙象般若功·战神",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的龙象般若功运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}

