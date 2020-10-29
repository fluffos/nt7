// This program is a part of NITAN MudLIB
// nizhuan.c

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object weapon;
        int skill;
        string msg;
        mapping buff, data;
        int time;

        if( userp(me) && !query("yuanshen", me) )
                return notify_fail("你还没有悟道，无法施展逆转九阴。\n");

        /*
        if( query("family/family_name", me) != "欧阳世家" )
                return notify_fail("你不是欧阳世家弟子，无法使用。\n");
        */

        if((int)me->query_skill("hamagong", 1) < 1000)
                return notify_fail("你的蛤蟆功不够娴熟，不会逆转九阴。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够。\n");

        if( query("jingli", me)<500 )
                return notify_fail("你的精力不够。\n");

        if( BUFF_D->check_buff(me, "hmg_nizhuan") )
                return notify_fail("你已经逆运了九阴。\n");
        
        if( userp(me) ) 
        {
                if( (time = BUFF_D->get_buff_overtime(me, "hmg_nizhuan2")) > 0 )
                        return notify_fail(MAG"神光离合消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }
        
        skill = me->query_skill("force");
        msg = HIB "$N" HIB "双手撑地，口中发出一连窜低喉声，一股股内劲勃发使$N" HIB "双足离地，呈头下足上之势。。\n" NOR;

        //tell_object(me, HIW "你感觉体内蛤蟆功随九阴逆转，好像有股巨大的力量要崩发出来一样。\n" NOR);
        
        data = ([
                "ap_power"  : 50,
                "add_damage": 100,
                "attack"    : skill,
                "defense"   : skill,
                "avoid_weak": 50, 
                "dispel_poison": skill / 3,
                "reduce_poison": 15,
                "str"       : skill/4,
        ]);
        
        addn("neili", -300, me);
        addn("jingli", -50, me);
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "hmg_nizhuan",
                "attr"  : "bless",
                "name"  : "蛤蟆功·逆转九阴",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你逆转九阴运功过久，经脉又渐渐复原。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        
        time  = 40;
        time -= ABILITY_D->check_ability(me, "cd-hmg-nizhuan"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd
                
        buff =  
        ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "hmg_nizhuan2",
                "attr"   : "curse",
                "name"   : "蛤蟆功·逆转九阴",
                "time"   : time,
                "buff_msg" : "逆转九阴消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
        ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}

