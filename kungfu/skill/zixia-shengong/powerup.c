// This program is a part of NT MudLIB
// powerup.c

#include <ansi.h>
inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill, damage;
        string msg;
        mapping buff, data;
        
        if( target != me ) 
                return notify_fail("你只能用紫霞神功提升自己的战斗力。\n");
                
        if( query("neili", me)<100 )
                return notify_fail("你的内力不够。\n");
                
        if( BUFF_D->check_buff(me, "powerup")/*
                || BUFF_D->check_buff(me,"dodgeup")
                || BUFF_D->check_buff(me,"atkup") */)
                return notify_fail("你已经在运用类似的武功了。\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        msg = MAG "$N微一凝神，运起紫霞神功，背转身去，脸上突然紫气大盛！只是那紫气一现即隐，转过身来，脸上又回复如常。\n" NOR;
        
        damage = skill/3;
        if( query("zixia_paper", me) )
                damage *= 2;
        
        data =  ([
                        "attack" : damage,
                        "defense": damage,
                ]);
        buff =
                ([
                        "caster": me,
                        "target": me,
                        "type"  : "powerup",
                        "attr"  : "bless",
                        "name"  : "紫霞神功·战神",
                        "time"  : skill,
                        "buff_data": data,      
                        "buff_msg" : msg,
                        "disa_msg" : "你的紫霞神功运行完毕，将内力收回丹田。\n",
                        
                ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}


