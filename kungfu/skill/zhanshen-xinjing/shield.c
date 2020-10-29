#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;
                mapping buff, data;
                string msg;

        if (target != me)
                return notify_fail("你只能用战神心经来提升自己的防御力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("zhanshen-xinjing", 1) < 50)
                return notify_fail("你的战神心经修为不够。\n");

        if( BUFF_D->check_buff(me, "shield") )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        msg = HIW "$N" HIW "默默凝神聚气，运起战神心经，顿时一股"
                        "白雾至身后腾起，笼罩全身。\n" NOR;

        data = ([
                "armor": skill/2, 
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "shield",
                "attr"  : "bless",
                "name"  : "战神心经·护体神功",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的战神心经运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}
