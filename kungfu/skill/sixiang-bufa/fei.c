#include <ansi.h>

inherit F_SSERVER;

string name() { return HIY "飞天神行" NOR; }

int perform(object me, object target)
{
        mapping buff, data;
        string msg;
        int count, skill;

        if( BUFF_D->check_buff(me, "dodgeup") )
                return notify_fail("你已经运起" + name() + "了。\n");

        if ((int)me->query_skill("sixiang-bufa", 1) < 150)
                return notify_fail("你的四象步法等级不够，难以施展" + name() + "。\n");

        if ((int)me->query_dex() < 33)
                return notify_fail("你的身法不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force", 1) < 150)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("dodge", 1) < 150)
                return notify_fail("你的轻功修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你此时的内力不足，难以施展" + name() + "。\n");

        msg = HIY "$N" HIY "足尖轻点地面，凌空跃起，身形顿时变得飘忽不定，难以捉摸。\n\n" NOR;
        
        skill = me->query_skill("sixiang-bufa", 1);

        count = skill / 40;

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
                "name"  : "四象步法·飞天神行",
                "time"  : skill/2,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的飞天神行运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);

        addn("neili", -200, me);
        return 1;
}
