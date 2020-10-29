// This program is a part of NT MudLIB

#include <ansi.h>
inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;
        int time;

        if( !query("yuanshen", me) )
                return notify_fail("你尚未悟道，无法使用寒魔玄力！\n");

        if( target != me )
                return notify_fail("你只能用冰蚕寒功来激发寒魔玄力。\n");

        if( (skill = me->query_skill("freezing-force", 1)) < 1500 )
                return notify_fail("你的冰蚕寒功修为不够，无法使用寒魔玄力！\n");

        if( me->query_skill("huagong-dafa", 1) < 1500 )
                return notify_fail("你的化功大法修为不够，无法使用寒魔玄力！\n");

        if( me->query_skill("poison", 1) < 1500 )
                return notify_fail("你对基本毒功的参悟还不够，无法使用寒魔玄力！\n");

        if( me->query_skill("force", 1) < 1500 )
                return notify_fail("你对基本内功的修为还不够，无法使用寒魔玄力！\n");

        if( BUFF_D->check_buff(me, "protectshield") )
                return notify_fail("你已经在运起寒魔玄力了。\n");

        if( query("jingli", me)<2000 )
                return notify_fail("你的真气不够。\n");

        if( query("neili", me)<5000 )
                return notify_fail("你的内力不够。\n");

        if( userp(me) ) 
        {
                if( (time = BUFF_D->get_buff_overtime(me, "freezing_hanmo")) > 0 )
                        return notify_fail(MAG"寒魔玄力消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }
        
        skill = me->query_skill("freezing-force", 1);
        addn("neili", -1000, me);
        me->receive_damage("qi", 0);

        message_combatd(HIB "$N" HIB "神色凝重，深吸一口气，体表瞬间变为靛蓝色，$N" HIB "随之摆出各种奇特的造型舞动着。\n"
                       "随着那些诡异的舞姿，蓝色烟气四起，在空中竟似显现无数异样蚕虫，在$N身周绕行不止，\n"
                       "四周温度骤降，只刹那间功夫，空气似乎都凝结了。\n" NOR, me);
        
        msg = HIB "这瞬间，$N" HIB "如同毒神附体，使人周身颤栗。\n" NOR;
        data = ([
                "unarmed_damage": skill*10,
                "avoid_freeze"  : 20,
                "add_freeze"    : 20,
                "add_poison"    : 60,
        ]);
        buff = ([
                "caster": me,
                "target": me,
                "type":"protectshield",
                "type2":"freezing",
                "attr":"bless",
                "name":"冰蚕寒功·寒魔玄力",
                "time":  skill/5,
                "buff_data":data,
                "buff_msg":msg,
                "shield_type":"neili",
                "shield_amount":skill*10000,
                "shield_desc":HIB"$n身边泛起一层寒气，将$N攻击阻在其外。\n"NOR,
                "disa_msg": HIB "$N" HIB "身形一滞，略显蹒跚，将冰蚕寒魔玄力收回丹田，"
                                "随着真气凝成的蚕虫纳入体内，\n$N" HIB"的体色恢复正常，周围的寒气也慢慢散开了。\n" NOR,
                "disa_type" : 1,
/*
                "shield_desc":HIW"$n"HIW"一触$N"HIW"衣衫，忽然全身大震，如遭电击。\n"NOR,
	        "shield_amount":skill,
	        "shield_type":"jing",
*/
        ]);
        BUFF_D->buffup(buff);
        
        buff =
        ([
                "caster":me,
                "target":me,
                "type":"damageshield",
                "att":"bless",
                "name":"冰蚕寒功·寒魔玄力",
                "buffup_name":"backfire",
                "buffup_type":"all",
                "buffup_ratio": 35,
                "buffup_msg":WHT"一阵锥心刺骨的寒冷沁进了$n"NOR+WHT"心中，$n"NOR+WHT"不由打了一个寒颤。\n"NOR,
                "time":skill/5,
                "buff_msg":WHT"$N"NOR+WHT"身法乍变，脸若冰霜，投足间阵阵冷风翻卷，刺骨凝寒。\n"NOR,
        ]);
        BUFF_D->buffup(buff);

        time = skill/5+40;
        time -= ABILITY_D->check_ability(me, "cd-freezing-hanmo"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd 
        buff =
        ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "freezing_hanmo",
                "attr"   : "curse",
                "name"   : "冰蚕寒功·寒魔玄力",
                "time"   : time,
                "buff_msg" : "寒魔玄力消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
        ]);
        BUFF_D->buffup(buff);
        //if( me->is_fighting() ) me->start_busy(2);
        return 1;
}
