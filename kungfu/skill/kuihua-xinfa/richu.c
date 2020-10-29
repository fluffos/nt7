// richu.c 日月光华 之 日出东方

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;
        int delta;

        if( userp(me) && query("gender", me) != "无性" && !query("special_skill/ghost",me))
                return notify_fail("你的性别与日月内功相斥，无法使用此绝招！\n");  

        if (target != me)
                return notify_fail("你只能用日月光华来提升自己的潜力。\n");

        if ((int)me->query_skill("kuihua-xinfa",1) < 100)
                return notify_fail("你的葵花心法修为太低，无法施展「日出东方」。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的内力不够。\n");

        if( BUFF_D->check_buff(me, "kuihua_richu") ) 
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -120, me);
        me->receive_damage("qi", 0);
        
        msg = HIR "$N" HIR "一声怪啸，双目变得赤红，双足一点，身子腾空而起，"
                    "四周顿时热浪翻涌，灸热难当。\n" NOR;

        delta = ABILITY_D->check_ability(me, "power-rygh-richu"); // 门派ab
        if( delta ) skill += skill*delta/100;
        data = ([
                "attack" : skill/3,
                "defense": skill/3,
                "damage" : skill*3,
                "dex"    : skill/20,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "kuihua_richu",
                "attr"  : "bless",
                "name"  : "葵花心法·日出东方",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的日出东方运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}
