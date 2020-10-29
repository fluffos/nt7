// This program is a part of NITAN MudLIB
// huaxue.c

#include <ansi.h>

#define HUAXUE "「" HIR "神刀化血" NOR "」"

inherit F_SSERVER;

int exert(object me, object target)
{
        object weapon;
        string msg;
        int skill,damage;
        mapping buff, data;
        int delta;
        
        if (target != me)
                return notify_fail("你只能用蚩尤狂战决来提升自己的战力。\n");
                
        if( BUFF_D->check_buff(me, "atkup") )
                return notify_fail("你已经在运功中了。\n");

        /*
        if (! me->is_fighting())
                return notify_fail(HUAXUE + "只能在战斗中使用。\n");
        */

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够！\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的蚩尤狂战决修为不够，不能使用" + HUAXUE + "！\n");

        weapon=query_temp("weapon", me);

        if( !objectp(weapon) || query("skill_type", weapon) != "blade" )
                return notify_fail("你没有装备刀，难以施展" + HUAXUE + "。\n");

        msg = HIR "$N" HIR "凝神闭目，右手持刀，左手顺着" + weapon->name() +
              HIR "刀刃一抹，鲜血顿时将" + weapon->name() + HIR "染红。\n待到$N"
              HIR "双目睁开，顿时杀气冲天！\n" NOR;

        skill = (int)me->query_skill("moshen-xinfa", 1) / 2 + (int)me->query_skill("chiyou-kuangzhanjue", 1); 
        damage = (int)me->query_skill("force") * 2;
        delta = ABILITY_D->check_ability(me, "da_power-cykzj-huaxue"); // 门派ab
        if( delta ) 
        {
             skill += skill*delta/100;
             damage += damage*delta/100;
        }
        addn("neili", -150, me);
        me->receive_damage("qi", 0);
        
        data = ([
                "damage" : damage,
                "blade"  : skill,
        ]);

        buff = ([
                "caster": me,
                "target": me,
                "type"  : "atkup",
                "attr"  : "bless",
                "name"  : "蚩尤狂战决·神刀化血",
                "time"  : skill/2,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的蚩尤狂战决之神刀化血运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}

