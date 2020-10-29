
#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;

        if( target != me )
                return notify_fail("你只能用五毒神功提升自己的战斗力。\n");
        if( query("neili", me)<100 )
                return notify_fail("你的内力不够。\n");
        if( BUFF_D->check_buff(me, "powerup") ) 
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        msg = BLU"$N运起五毒神功，头顶黑气蒸腾，全身肌肤坟起黑色的鳞甲，双目凶光四射！\n" NOR;
        
        data = ([
                "attack" : skill/3,
                "hand"   : skill/3,
                "defense": skill/3,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "五毒神功·战神",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的五毒神功运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
 
        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}
