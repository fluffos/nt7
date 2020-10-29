#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        mapping buff, data;
        string msg;
        int count, skill;

        if( BUFF_D->check_buff(me, "dodgeup") )
                return notify_fail("你已经运起「九阴归元」了。\n");

        if ((int)me->query_skill("shexing-lifan", 1)< 150)
                return notify_fail("你的蛇行狸翻等级不够，难以施展此项绝技！\n");

        if ((int)me->query_dex() < 30)
                return notify_fail("你的身法不够使用「九阴归元」绝技！\n");

        if ((int)me->query_skill("force", 1)< 150)
                return notify_fail("你的内功火候不够，难以施展此项绝技！\n");

        if ((int)me->query_skill("dodge", 1)< 150)
                return notify_fail("你的轻功修为不够，不会使用此项绝技！\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力修为不够使用「九阴归元」！\n");

        if( query("neili", me)<250 )
                return notify_fail("你此时的内力不足！\n");

        msg = HIW "$N" HIW "运起九阴真气，双臂骨骼一阵爆响，身形一展，整"
                  "个人顿时凌空飘起，速度变得异常敏捷。\n" NOR;
        

        skill = me->query_skill("shexing-lifan", 1);

        count = skill / 50;

        if (me->is_fighting())
                me->start_busy(2);
        
        data = ([
                "str": count,
                "dex": count,
        ]);
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "dodgeup",
                "attr"  : "bless",
                "name"  : "蛇行狸翻·九阴归元",
                "time"  : skill/2,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的九阴归元运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        addn("neili", -200, me);
        return 1;
}
