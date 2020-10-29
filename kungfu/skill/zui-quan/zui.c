// zui.c 罗汉醉酒

#include <ansi.h>

#define PFM_NAME        "罗汉醉酒"

inherit F_SSERVER;

int perform(object me, object target)
{
        mapping buff, data;
        string msg;
        int count;
        int skill;
 
        if( query("neili", me)<150 )
                return notify_fail("你的真气不足以施展「" + PFM_NAME + "」。\n");

        if( BUFF_D->check_buff(me, "zuiquan_zui") )
                return notify_fail("你已经竭力提升你的身法了。\n");
        
        if ((int)me->query_skill("zui-quan", 1) < 80)
                return notify_fail("你的醉拳还不到家，无法施展「" + PFM_NAME + "」。\n");

        msg = HIY "$N" HIY "忽地身形一变，双拳虚握，使出一招「" + PFM_NAME +
              HIY "」，犹如金杯在手。\n"
              HIG "看似步履踉跄，醉态可拘，但身形却灵活之极！\n" NOR;

        addn("neili", -100, me);

        skill = me->query_skill("zui-quan", 1);
        count = skill / 50 + (int)me->query_condition("drunk") / 50;
        
        data = ([
                "dex": count, 
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "醉拳·罗汉醉酒",
                "time"  : skill/3,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的罗汉醉酒运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        me->start_busy(1 + random(3));
        return 1;
}
