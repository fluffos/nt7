#include <ansi.h>

string name() { return MAG "剑心通明" NOR; }

inherit F_SSERVER;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        mapping buff, data;
        object weapon;
        string msg;
        int skill;

        if( !query("yuanshen", me) )
                return notify_fail("你还没有悟道，还不能施展"+name()+"。\n");

        if (me->query_skill_mapped("sword") != "lonely-sword")
                return notify_fail("你还没有激发独孤九剑。\n");

        if( !query("lonely-sword/nothing", me) )
                return notify_fail("你还没有进入无招境界，何谈剑心通明？\n");

        if ((int)me->query_skill("lonely-sword", 1) < 1000)
                return notify_fail("你的独孤九剑等级不够，难以施展" + name() + "。\n");

        if( BUFF_D->check_buff(me, "dgjj_jian") ) 
                return notify_fail("你已经运起" + name() + "了。\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你所使用的武器不对！\n");

        if( query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不对！\n");

        if( query("neili", me)<250 )
                return notify_fail("你此时的内力不足，难以施展" + name() + "。\n");

        msg = MAG "$N" MAG "凝神聚气，挥洒手中兵器，进入无招无我，剑心通明境界！\n\n" NOR;

        if (me->is_fighting())
                me->start_busy(1);

        skill = me->query_skill("lonely-sword", 1);

        data = ([
                "damage": skill*3,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "dgjj_jian",
                "attr"  : "bless",
                "name"  : "独孤九剑·剑心通明",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的剑心通明运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);

        addn("neili", -200, me);
        return 1;
}