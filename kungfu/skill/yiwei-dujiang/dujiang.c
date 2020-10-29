#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        mapping buff, data;
        object weapon;  
        string msg;
        int count, cnt, skill;

        if( BUFF_D->check_buff(me, "dodgeup") )
                return notify_fail("你已经运起「一苇渡江」了。\n");

        if ((int)me->query_skill("yiwei-dujiang", 1)< 150)
                return notify_fail("你的一苇渡江等级不够，难以施展此项绝技！\n");

        if ((int)me->query_dex() < 30)
                return notify_fail("你的身法不够使用「一苇渡江」绝技！\n");

        if ((int)me->query_skill("force", 1)< 150)
                return notify_fail("你的内功火候不够，难以施展此项绝技！\n");

        if ((int)me->query_skill("dodge", 1)< 150)
                return notify_fail("你的轻功修为不够，不会使用此项绝技！\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力修为不够使用「一苇渡江」！\n");

        if( query("neili", me)<250 )
                return notify_fail("你此时的内力不足！\n");

        msg = HIB "$N" HIB "运起心意气混元功，施展「一苇渡江」绝技,"
                  "身形一展，整个人顿时凌空飘起，身体变得越来越轻。\n" NOR;
        
        message_combatd(msg, me, target);
        skill = me->query_skill("yiwei-dujiang", 1);
        cnt =(int)( (int)me->query_condition("drunk") / 3);

        count = skill / 50 + cnt;

        if (me->is_fighting())
                me->start_busy(2);
        
        data = ([
                "dex": count,
        ]);
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "dodgeup",
                "attr"  : "bless",
                "name"  : "一苇渡江·一苇渡江",
                "time"  : skill/2,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的一苇渡江运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);

        addn("neili", -200, me);
        return 1;
}
