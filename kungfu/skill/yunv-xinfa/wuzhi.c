// Written by Lonely@nitan.org
// 所向无滞 转世技能
// wuzhi.c

#include <ansi.h>
inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;
        int time;

        /*
        if( query("family/family_name", me) != "古墓派" )
                return notify_fail("你不是古墓弟子，无法使用所向无滞。\n");
        */

        if( userp(me) && !query("yuanshen", me) )
                return notify_fail("你尚未悟道，无法使用所向无滞！\n");

        if( (skill = me->query_skill("yunv-xinfa", 1)) < 1000 )
                return notify_fail("你的玉女心法还不够精熟，无法使用所向无滞！\n");

        if( BUFF_D->check_buff(me, "ynxf_wuzhi") )
                return notify_fail("你已经在运起所向无滞了。\n");

        if( query("jingli", me)<2000 )
                return notify_fail("你的真气不够。\n");

        if( query("neili", me)<5000 )
                return notify_fail("你的内力不够。\n");
        
        if( userp(me) ) 
        {
                if( (time = BUFF_D->get_buff_overtime(me, "ynxf_wuzhi2")) > 0 )
                        return notify_fail(MAG"所向无滞消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }
        
        addn("neili", -1000, me);
        me->receive_damage("qi", 0);

        skill += me->query_skill("martial-cognize", 1);
        skill /= 100;

        msg = HIY "只见$N" HIY "心静如水，内息再无停滞，心中武学如流水般挥洒开来。\n" NOR;

        data = ([
                "ap_power": skill,
                "add_weak": skill,
                "add_busy": skill/6,
                "double_damage": skill,
        ]);

        buff = ([
                "caster": me,
                "target": me,
                "type"  : "ynxf_wuzhi",
                "attr"  : "bless",
                "name"  : "玉女心法·所向无滞",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的所向无滞运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        
        time  = 40;
        time -= ABILITY_D->check_ability(me, "cd-ynxf-wuzhi"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd 
                
        buff =  
	([
	        "caster" : me,
	        "target" : me,
	        "type"   : "cooldown",
	        "type2"  : "ynxf_wuzhi2",
	        "attr"   : "curse",
	        "name"   : "玉女心法·所向无滞",
	        "time"   : time,
	        "buff_msg" : "所向无滞消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
	        "disa_msg" : "",
	        "disa_type": 0,
	]);
	BUFF_D->buffup(buff);
	
        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}
