// by sinb

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        int i;
        string msg;
        
        if (me->query_condition("killer") &&
            query("no_fight", environment(me)) )
        {
                tell_object(me, HIR "你发现你的明玉功好象受到限制，气血未能自动恢复！\n" NOR );
        }
        else if( query("neili", me) < 10000 )
        {
                tell_object(me, HIR "你发现你的内力不够，气足无法发挥，气血未能自动恢复！\n" NOR );
        }
        else
        {
                tell_object(me, HIR "你的明玉功发挥了奇效，感觉损失的气血在慢慢恢复！\n" NOR );
                message_vision(HIW "$N眼睛中射出异样光芒，身上的伤口奇迹般地慢慢愈合。。\n" NOR, me);
        
                addn("eff_qi",query("max_qi", me)/20, me);
                addn("qi",query("eff_qi", me)/20, me);
                if( query("eff_qi", me) > query("max_qi", me) )
                        set("eff_qi",query("max_qi", me), me);
                if( query("qi", me) > query("max_qi", me) )
                        set("qi",query("eff_qi",  me), me);
                addn("neili", -10000, me);
        }
        
        me->apply_condition("mingyu_qizu", duration - 1);
        
        if( duration < 1 ) 
        {
                message_vision(HIC "$N的「气足」奇功运行完毕，脸色顿时一片苍白。\n" NOR, me);

                return 0;
        }
        return CND_CONTINUE;
}
