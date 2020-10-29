// powerup.c 玉女心经加力

#include <ansi.h>
inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;

        if( target != me )
                return notify_fail("你只能提升自己的战斗力。\n");
        if( query("neili", me)<200 )
                return notify_fail("你的内力不够。\n");
        if( BUFF_D->check_buff(me, "powerup") ) 
                return notify_fail("你已经在运功中了。\n");
        if( (int)me->query_skill("yunv-xinfa",1) < 80)
                return notify_fail("你的玉女心法还不够精熟。\n");

        skill = me->query_skill("force");

        msg = HIC "$N脸色微微一沉，双掌向外一分，姿势曼妙，如一朵"HIW"白玉兰花"HIC"盛开在初冬的寒风中！\n" NOR;

        addn("neili", -100, me);

        data = ([
                "attack" : skill/3,
                "defense": skill/3,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "玉女心法·战神",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的玉女心法运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);

        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}

