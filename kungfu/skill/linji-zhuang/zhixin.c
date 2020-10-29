// zhixin.c

#include <ansi.h>

int exert(object me, object target)
{
        mapping buff, data;
        string msg;        
        int level = me->query_skill("linji-zhuang", 1);

        if (level < 60) return notify_fail("你的临济十二庄修为还不够。\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("你的内力还不够强。\n");

        if( query("neili", me)<4*level )
                return notify_fail("你的真气不够。\n");

        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("你已经受伤过重，只怕一运真气便有生命危险！\n");

        if( BUFF_D->check_buff(me, "ljz_zhixin") ) 
                return notify_fail("你已经运用之心二庄凝聚心神了。\n");
                
        msg = HIY + "只见$N微一凝神，吞吐几口长气，一对眼眸灵动晶亮，神采弈弈。\n" NOR;

        addn("neili", -4*level, me);
        level += me->query_skill("literate", 1);
        level = 50+level/3+random(level/10);
        data = ([
                "int": level / 8,
        ]);
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "ljz_zhixin",
                "attr"  : "bless",
                "name"  : "临济十二庄·之心",
                "time"  : level,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : HIG"你体内已积过多浊气，似乎领悟力又归于寻常。\n"NOR,
                        
        ]);
        BUFF_D->buffup(buff);
        tell_object(me, HIY "你微一凝神，运动之心两庄，去浊气出体外，收清气入心中，只觉灵台清明，领悟力似乎有所增加。\n" NOR);

        return 1;
}
