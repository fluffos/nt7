// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_SSERVER;

string name() { return "封魔"; }

int perform(object me)
{
        object weapon;
        int skill;
        string msg;
        mapping buff, data;

        if( (int)me->query_skill("banruo-zhang", 1) < 60 )
                return notify_fail("你的般若掌法不够娴熟，不会使用「封魔」。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，无法使用「封魔」。\n");

        if( BUFF_D->check_buff(me,"brz_feng") )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("banruo-zhang", 1);
        msg = HIG "$N" HIG "使出般若掌「封魔」式，双掌翻飞将周身护住。\n" NOR;
        
        data = ([
                "attack" : -skill/4,
                "defense":  skill/3,
        ]);
        
        buff = ([
                "caster": me,
	        "target": me,
                "type"  : "brz_feng",
	        "attr"  : "bless",
	        "name"  : "般若掌·封魔",
	        "time"  : skill/4,
	        "buff_data": data,	
	        "buff_msg" : msg,
	        "disa_msg" : "你的般若掌「封魔」运行完毕，将内力收回丹田。\n",
        ]);
         BUFF_D->buffup(buff); 

        addn("neili", -100, me);
        if (me->is_fighting()) me->start_busy(2);

        return 1;
}
