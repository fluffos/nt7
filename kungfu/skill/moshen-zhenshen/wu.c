// protect

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return "无法无天"; }

int perform(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("moshen-zhenshen", 1) < 100)
                return notify_fail("你的魔神真身修为不够。\n");

        if( BUFF_D->check_buff(me, "mszs_wu") ) 
                return notify_fail("你已经运起魔神真身绝招无法无天了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        msg = HIY "$N" HIY "默运魔功，内劲在身体内快速的运转，霎时在体外形成一层罡气！\n" NOR;
        
        data = ([
                "armor" : skill/2,
                "defense": skill/3,
        ]);
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "mszs_wu",
                "attr"  : "bless",
                "name"  : "魔神真身·无法无天",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的无法无天运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}
