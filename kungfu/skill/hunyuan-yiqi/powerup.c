// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;

        if( target != me ) return notify_fail("你只能用混元一气功提升自己的战斗力。\n");

        if( query("neili", me)<100)return notify_fail("你的内力不够。\n");
        if( BUFF_D->check_buff(me, "powerup") )return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        addn("force", -100, me);
        me->receive_damage("qi", 0);

        msg = HIR "$N长吸一口气，运起混元一气功已将全身潜力尽数提起！\n" NOR;

        data = ([
                "attack" : skill/3,
                "defense": skill/3,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "混元一气功·战神",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的混元一气功运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}


