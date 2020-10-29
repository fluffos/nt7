// This program is a part of NT MudLIB
// powerup.c

#include <ansi.h>
inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;
        string msg;
        mapping buff, data;

        if( target != me )
                return notify_fail("你只能提升自己的战斗力。\n");
                
        if( query("neili", me)<200 )
                return notify_fail("你的内力不够。\n");
                
        if( BUFF_D->check_buff(me, "powerup") /*
                || BUFF_D->check_buff(me,"dodgeup")
                || BUFF_D->check_buff(me,"atkup")*/ )
                return notify_fail("你已经在运用类似的武功了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);
        
        msg = HIR "$N舌尖一咬，喷出一口鲜血，运起易筋经神功已将全身潜力尽数提起！\n" NOR;

        data =
        ([
                "attack" : skill/2, 
                "defense": skill/2, 
        ]);
        buff =
        ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "易筋经神功·战神",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的易筋经神功运行完毕，将内力收回丹田。\n",                  
        ]);
        
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}
