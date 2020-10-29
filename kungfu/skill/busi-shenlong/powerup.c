// This program is a part of NT MudLIB
// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;
        mapping buff, data;
        string msg;

        if( target != me ) 
                return notify_fail("你只能用不死神龙大法提升自己的战斗力。\n");

        if( (int)me->query_skill("busi-shenlong",1) < 50 )
                return notify_fail("你的内功火候还不够，无法使用不死神龙大法！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够!\n");
                
        if( BUFF_D->check_buff(me, "powerup") )
                return notify_fail("你已经在运用类似的武功了。\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        msg = HIR "$N双目赤红，纵声大呼：洪教主神通护佑，众弟子勇气百倍，以一当百，以百当万！\n"NOR;
        //tell_object(me,HIW"你顿时感觉武功大进，劲力比先前大了数倍！\n" NOR);
        
        data = ([
                "attack" : skill/3,
                "defense": skill/3,
        ]);
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "不死神龙·战神",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的不死神龙大法运行完毕，汗如泉涌，呼呼喘气。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}
