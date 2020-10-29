// This program is a part of NT MudLIB
// jiuyang.c

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;
        string msg;
        mapping buff, data;

        if( !query("can_exert/yijinjing/jiuyang", me) )
                return notify_fail("你还没有领悟过少林九阳真气呢！\n");

        if ((int)me->query_skill("yijinjing", 1) < 140)
                return notify_fail("你的易筋经修为如此之浅还想运用九阳真气？\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的内力修为太差，多多打坐吧。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真气不够。\n");

        if( /*BUFF_D->check_buff(me, "powerup")
                || BUFF_D->check_buff(me,"dodgeup")
                || */BUFF_D->check_buff(me,"atkup") )
                return notify_fail("你已经在运用类似的武功了。\n");

        
        msg = HIR"\n$N潜运少林九阳神功，体内真气澎湃不息，全身佛光流动，宝相庄严！\n" NOR;
        
        skill = me->query_skill("yijinjing",1);
        addn("neili", -300, me);
        me->receive_damage("qi", 0);
        
        data =
        ([
                "attack" : skill/2,
        ]);
        buff =
        ([
                "caster": me,
                "target": me,
                "type"  : "atkup",
                "attr"  : "bless",
                "name"  : "易筋经·九阳真气",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你将九阳真气收回丹田，面露慈祥笑容。\n",                  
        ]);      
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(2);

        return 1;       
}
