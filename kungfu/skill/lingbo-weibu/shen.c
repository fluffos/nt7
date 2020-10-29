// This program is a part of NITAN MudLIB

#include <ansi.h>

string name() { return MAG "神光离合" NOR; }

int perform(object me, object target)
{
        string msg;
        mapping buff;
        int time;

        if( userp(me) && !query("yuanshen", me) )
                return notify_fail("你尚未悟道，无法施展" + name() + "。\n" NOR);

        if( me->query_skill("lingbo-weibu", 1) < 1000 )
                return notify_fail("你的凌波微步还不够熟练，难以施展" + name() + "。\n" NOR);

        if( query("jingli", me)<2000 )
                return notify_fail("你现在真气不足，难以施展" + name() + "。\n" NOR);

        if( query("neili", me)<5000 )
                return notify_fail("你现在内力不够，难以施展" + name() + "。\n" NOR);

        if( BUFF_D->check_buff(me, "lbwb-shen") ) 
                return notify_fail("你已经运起" + name() + "。\n" NOR);

        if( userp(me) ) 
        {
                if( (time = BUFF_D->get_buff_overtime(me, "lbwb_shen")) > 0 )
                        return notify_fail(MAG"神光离合消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);      

        msg = MAG "\n$N" MAG "提起真气，施展" + name() + MAG "，身形虚晃，神光交错，离合难分，让人难以看清所在。\n" NOR;
        
        buff = ([
                "caster":me,
                "target":me,
                "type"  :"lbwb-shen",
                "attr"  :"bless",
                "name"  :"凌波微步·神光离合",
                "time"  : 30,
                "buff_data":"immortal",
                "buff_msg" :msg,
                "disa_msg" :HIY"你的「神光离合」运功完毕，将内力收回丹田。\n"NOR        ,
        ]);
        BUFF_D->buffup(buff);
        
        time = 70;
        time -= ABILITY_D->check_ability(me, "cd-lbwb-shen"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd 
        buff =  
	([
	        "caster" : me,
	        "target" : me,
	        "type"   : "cooldown",
	        "type2"  : "lbwb_shen",
	        "attr"   : "curse",
	        "name"   : "凌波微步·神光离合",
	        "time"   : time,
	        "buff_msg" : "神光离合消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
	        "disa_msg" : "",
	        "disa_type": 0,
	]);
	BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(2);
        return 1;

}
