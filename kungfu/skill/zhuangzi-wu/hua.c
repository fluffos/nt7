#include <ansi.h>

#define HUA "「" MAG "化蝶" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        mapping buff, data;
        object weapon;  
        string msg;
        int count, cnt, skill;

        if( BUFF_D->check_buff(me, "dodgeup") )
                return notify_fail("你已经运起" HUA "了。\n");

        if ((int)me->query_skill("zhuangzi-wu", 1) < 150)
                return notify_fail("你的庄子舞等级不够，难以施展" HUA "。\n");

        if ((int)me->query_dex() < 32)
                return notify_fail("你的身法不够，难以施展" HUA "。\n");

        if ((int)me->query_skill("force", 1) < 150)
                return notify_fail("你的内功火候不够，难以施展" HUA "。\n");

        if ((int)me->query_skill("dodge", 1) < 150)
                return notify_fail("你的轻功修为不够，难以施展" HUA "。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力修为不够，难以施展" HUA "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你此时的内力不足，难以施展" HUA "。\n");

        msg = MAG "$N" MAG "一声清啸，身形一展，舞步宛如行云流水、彩碟飞"
              "扬，速度变得异常敏捷。\n\n" NOR;
        
        
        skill = me->query_skill("zhuangzi-wu", 1);
        cnt = (int)((int)me->query_condition("drunk") / 50);

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
                "name"  : "庄子舞·化蝶",
                "time"  : skill/2,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的化蝶运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);

        addn("neili", -200, me);
        return 1;
}
