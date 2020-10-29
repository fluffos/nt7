// This program is a part of NITAN MudLIB

#include <ansi.h>

string name() { return MAG "挪转乾坤" NOR; }

int perform(object me, object target)
{
        mapping buff, data;
        string msg;
        int level;
        int time;

        if( !userp(me) && !query("yuanshen", me) )
                return notify_fail("你尚未悟道，无法施展" + name() + "。\n" NOR);

        if( (level = me->query_skill("qiankun-danuoyi", 1)) < 1000 )
                return notify_fail("你的乾坤大挪移还不够熟练，难以施展" + name() + "。\n" NOR);

        if( (int)query("jingli", me) < 2000 )
                return notify_fail("你现在真气不足，难以施展" + name() + "。\n" NOR);

        if( (int)query("neili", me) < 5000 )
                return notify_fail("你现在内力不够，难以施展" + name() + "。\n" NOR);

         if (BUFF_D->check_buff(me,"qkdny-nuozhuan") )
                return notify_fail("你已经运起" + name() + "。\n" NOR);

        if( userp(me) ) 
        {
                if( (time = BUFF_D->get_buff_overtime(me, "qkdny_nuozhuan")) > 0 )
                        return notify_fail(MAG"挪转乾坤消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);

        msg = MAG "\n$N" MAG "提起真气，默念" + name() + "心法，心中卸力拆招的法门已达发乎自然之境。\n" NOR;

        buff = ([
                "caster": me,
                "target": me,
                "type"  : "qkdny-nuozhuan",
                "attr"  : "bless",
                "name"  : "乾坤大挪移·挪转乾坤",
                "time"  : level,
                "buff_data": "nuozhuan",      
                "buff_msg" : msg,
                "disa_msg" : "你的「挪转乾坤」运功完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);

        time = level+40;
        time -= ABILITY_D->check_ability(me, "cd-qkdny-nuozhuan"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd

        buff =
        ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "qkdny_nuozhuan",
                "attr"   : "curse",
                "name"   : "乾坤大挪移·挪转乾坤",
                "time"   : time,
                "buff_msg" : "挪转乾坤消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
        ]);
        BUFF_D->buffup(buff);

        if( me->is_fighting() ) me->start_busy(2);
        return 1;
}
