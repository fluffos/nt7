
// suxin.c


#include <ansi.h>

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int level = me->query_skill("suxin-jue", 1);

        if (level < 120) return notify_fail("你的内功修为还不够。\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("你的内力还不够强。\n");

        if( query("neili", me)<4*level )
                return notify_fail("你的真气不够。\n");

        if( BUFF_D->check_buff(me, "powerup") ) 
                return notify_fail("你此时正在按素心诀的心法行功。\n");

        write( HIW "你暗运玉女素心心法，把多年修炼的“十二少、十二多”的正反要诀发挥到极致。\n" NOR);
        msg =  HIW + "只见$N微闭双眼，无喜无乐，无思无虑,把多年修炼的“十二少、十二多”的正反要诀发挥到极致。\n" NOR;

        addn("neili", -level, me);
        
        data = ([
                "armor"  : level,
                "defense": level,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "素心诀·玉女素心",
                "time"  : level/5,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : HIG"你行功已久，慢慢收回玉女素心的心法。\n"NOR,
                        
        ]);
        BUFF_D->buffup(buff);
        
        if( me->is_fighting() ) me->start_busy(3);
        return 1;
}
