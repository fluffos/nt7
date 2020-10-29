// This program is a part of NITAN MudLIB
// shield.c 护体神功

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;

        if( target != me ) 
                return notify_fail("你只能用小无相功来运护体神功。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够。\n");
                
        if( BUFF_D->check_buff(me, "shield") )
                return notify_fail("你已经在运功\中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        msg = MAG "$N长吸一口气，运起护体神功，身上衣衫缓缓涨起。ⅵ\n" NOR;

        data = ([
                "armor" : skill/2,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "shield",
                "attr"  : "bless",
                "name"  : "小无相功·护体神功",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的小无相功运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);

        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}
