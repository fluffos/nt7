// linji_daxiao.c
#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        if( duration == 0 )
        {
                tell_object(me, 
                        HIB "忽然你全身感到一阵乏力，一肚皮不自在，原来你的大小庄收功了！\n" NOR );
                addn("max_jing",query("linji/jing",  me), me);
                addn("eff_jing",query("linji/jing",  me), me);
                addn("jing",query("linji/jing",  me), me);
                addn("max_qi", 0-2*query("linji/jing", me), me);
                if( query("eff_qi", me)>query("max_qi", me) )
                        set("eff_qi",query("max_qi",  me), me);
                if( query("qi", me)>query("eff_qi", me) )
                        set("qi",query("eff_qi",  me), me);
                if( query("eff_jing", me)>query("max_jing", me) )
                        set("eff_jing",query("max_jing",  me), me);
                if( query("jing", me)>query("eff_jing", me) )
                        set("jing",query("eff_jing",  me), me);
                delete("linji/jing", me);
                me->save();
                return 0;
        }
        me->apply_condition("linji_daxiao", duration - 1);

        return CND_CONTINUE;
}

string query_type(object me)
{
        return "force";
}