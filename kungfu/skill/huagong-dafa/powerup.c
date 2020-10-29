// This program is a part of NITAN MudLIB
// powerup.c 化功大法加力

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
                return notify_fail("你的内力不够。\n");
        if( BUFF_D->check_buff(me, "powerup") )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        msg = HIG "$N舌尖一咬，喷出一口碧血，运起化功大法已将全身潜力尽数提起！\n" NOR;

        data = ([
                "attack" : skill/3,
                "defense": skill/3,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "化功大法·战神",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的化功大法运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}


