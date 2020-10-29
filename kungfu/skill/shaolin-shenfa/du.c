#include <ansi.h>

string name() { return HIY "一苇渡江" NOR; }

inherit F_SSERVER;

void remove_effect(object me, int amount, int amount1);

int perform(object me, object target)
{
        mapping buff, data;
        object weapon;
        string msg;
        int count, skill;

        if( BUFF_D->check_buff(me, "dodgeup") )
                return notify_fail("你已经运起" + name() + "了。\n");

        if ((int)me->query_skill("shaolin-shenfa", 1) < 150)
                return notify_fail("你的少林身法等级不够，难以施展" + name() + "。\n");

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

        msg = HIY "$N" HIY "足尖轻点地面，施展一苇渡江，凌空跃起，身形顿时变得轻松自如。\n\n" NOR;

        skill = me->query_skill("shaolin-shenfa", 1);

        count = skill / 50;

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
                "name"  : "少林身法·一苇渡江",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的一苇渡江运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        addn("neili", -200, me);
        return 1;
}
