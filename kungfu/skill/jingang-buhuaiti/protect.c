// This program is a part of NT MudLIB
// Written by Lonely@nitan.org

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return "金刚不坏"; }
int perform(object me, object target)
{
        mapping buff;
        int duration;
        int skill;
        int time;

        if( query("neili", me) < 100 )
                return notify_fail("你的内力不够。\n");

        if( me->query_skill("jingang-buhuaiti", 1) < 200 )
                return notify_fail("你的金刚不坏护体神功修为不够。\n");
        
        if( BUFF_D->check_buff(me, "prtshield") ) 
                return notify_fail("你正在施展类似技艺，无法使用金刚不坏体神功。\n");
                
        if( BUFF_D->check_buff(me, "protect") ) 
                return notify_fail("你正在施展金刚不坏护体神功。\n");

        if( userp(me) ) {
                if( (duration = BUFF_D->get_buff_overtime(me, "jgbht_protect")) > 0 )
                        return notify_fail(MAG"『金刚不坏』消耗心神太甚，还需等待"+duration+"秒。\n"NOR);
        }
        
        skill = me->query_skill("jingang-buhuaiti");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        buff =
                ([
                        "caster":me,
                        "target":me,
                        "type":"prtshield",
                        "type2":"protect",
                        "attr":"bless",
                        "name":"金刚不坏体·金刚不坏",
                        "shield_type":"neili",
                        "shield_amount":skill*10000,
                        "shield_desc":BBLU HIY"卍"NOR CYN" $n"CYN"梵音声声，"CYN"周身被"HIY"金光"NOR CYN"笼罩住，$N丈外皆不可进。 "NOR BBLU HIY"卍\n"NOR,
                        "time":  skill/5,
                        "buff_msg": HIY "只听$N" HIY "高呼佛号，全身肌肉紧缩，霎那间皮肤竟犹如镀金一般，发出灿灿金光。\n" NOR,
                        //"buff_msg": BBLU HIY"卍"NOR CYN" $n"CYN"魅影悬梭，"CYN"周身被"HIR"血魔化影"NOR CYN"笼罩住，$N"CYN"丈外皆不可进。 "NOR BBLU HIY"卍\n"NOR,
                        "disa_msg": "你的金刚不坏护体神功运行完毕，将内力收回丹田。\n",
                        "disa_type": 1,
                ]);
                                
        BUFF_D->buffup(buff);

        time = skill/5+40;
        time -= ABILITY_D->check_ability(me, "cd-jgbht-protect"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd
         
	buff = 
	        ([
	                "caster":me,
	                "target":me,
	                "type":"cooldown",
	                "type2":"jgbht_protect",
	                "attr": "curse",
	                "name":"金刚不坏体·金刚不坏",
	                "time":time,
	                "buff_msg":"『金刚不坏』消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
	                "disa_msg":"",
	                "disa_type": 0,
	        ]);
	        
	BUFF_D->buffup(buff);
        //if( me->is_fighting() ) me->start_busy(2);
        
        return 1;
}
