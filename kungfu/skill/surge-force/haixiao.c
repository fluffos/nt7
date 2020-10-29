// powerup.c 海天一啸

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;
        int delta;

        if (target != me)
                return notify_fail("你只能用怒海狂涛来提升自己的战斗力。\n");

        if( query("gender", me) != "男性"  )
                return notify_fail("你不具有男性的阳刚之气，无法使用海天一啸。\n");
        if( query("neili", me)<100 )
                return notify_fail("你的内力不够。\n");

        if( BUFF_D->check_buff(me, "nhkt_haixiao") ) 
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        msg = HIW "$N" HIW "仰天长啸，气势如山洪爆发，丹田内力迅速游遍全身！！\n" NOR;

        if( query("can_perform/surge-force/new", me) ) skill *= 3; 
     
        delta = ABILITY_D->check_ability(me, "power-nhkt-haixiao"); // 门派ab
        if( delta ) skill += skill*delta/100;
        data = ([
                "attack" : skill*2/5,
                "defense": skill*2/5,
                "damage":skill,
        ]);

        buff = ([
                "caster": me,
                "target": me,
                "type"  : "nhkt_haixiao",
                "attr"  : "bless",
                "name"  : "怒海狂涛·海天一啸",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的怒涛潮涌运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}
