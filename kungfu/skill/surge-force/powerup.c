// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;

        if (target != me)
                return notify_fail("你只能用怒涛潮涌提升自己的战斗力。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够。\n");

        if( BUFF_D->check_buff(me, "powerup") || query_temp("surge_powerup",me)) 
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        addn("neili", -200, me);
        me->receive_damage("qi", 0);

        msg = HIC "$N" HIC"一声长啸，激起一阵狂风，气"
                        "浪翻翻滚滚，向两旁散开。\n霎时之间，便"
                        "似长风动起，气云聚合，天地渺然，有如海"
                        "浪滔滔。\n" NOR;
        
        if (query("can_perform/surge-force/new", me))skill *= 3;
        
        data = ([
                "attack" : skill*2/5,
                "defense": skill*2/5,
                "unarmed_damage":skill,
                "armor"  : skill/3,
        ]);
                set_temp("surge_powerup",1,me);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me,
                              skill :), skill);

        buff = ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "怒海狂涛·战神",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的怒涛潮涌运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}
void remove_effect(object me, int count)
{
        delete_temp("surge_powerup", me);
}

