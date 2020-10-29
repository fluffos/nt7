// This program is a part of NITAN MudLIB
// Written by Lonely@nitan.org
// protect.c 提高灵鹫宫的威力

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;
        string msg;
        mapping buff;
        int time;

        if( target != me )
                return notify_fail("你只能用八荒六合唯我独尊来提升自己的防御。\n");

        if( BUFF_D->check_buff(me,"prtshield")
                || BUFF_D->check_buff(me,"protect") )
                return notify_fail("你已经在运用类似的武功了。\n");
                
        if( query("neili", me) < 150 )
                return notify_fail("你的内力不够。\n");

        if( (int)me->query_skill("bahuang-gong", 1) < 100 )
                return notify_fail("你的八荒六合唯我独尊修为不够。\n");
        
        if( userp(me) ) {
                if( (time = BUFF_D->get_buff_overtime(me, "bhg_protect")) > 0 )
                        return notify_fail(MAG"八荒六合功的唯我独尊神功消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }
        
        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        
        msg = HIW "$N" HIW "身子一晃，全身周围形成一层层罡气，罡气逼人！\n" NOR;

        buff =
                ([
                        "caster":me,
                        "target":me,
                        "type":"prtshield",
                        "type2":"protect",
                        "attr":"bless",
                        "name":"八荒六合功·唯我独尊",
                        "shield_type":"neili",
                        "shield_amount":skill*150,
                        "shield_desc":WHT"$n身边泛起一层层罡气，将$N攻击阻在其外。\n"NOR,
                        "time":  skill/5,
                        "buff_msg": msg,
                        "disa_msg": "你的八荒六合唯我独尊运行完毕，将内力收回丹田。\n",
                        //"disa_type": 1,
                ]);

        BUFF_D->buffup(buff);

        time = skill/5+30;
        time -= ABILITY_D->check_ability(me, "cd-bhg-protect"); // ab门派减cd
                
        buff = 
                ([
                        "caster" : me,
                        "target" : me,
                        "type"   : "cooldown",
                        "type2"  : "bhg_protect",
                        "attr"   : "curse",
                        "name"   : "八荒六合功·唯我独尊",
                        "time"   : time,
                        "buff_msg" : "八荒六合功的唯我独尊神功消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                        "disa_msg" : "",
                        "disa_type": 0,
                ]);
        BUFF_D->buffup(buff);

        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}
