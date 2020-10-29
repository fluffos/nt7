// mj_shouwei.c

#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{
        if (duration < 1) {
                tell_object(me, HIW "守卫时间已到，快回去复命(task ok)吧！\n" NOR);
        set_temp("shouwei_ok", 1, me);
                return 0;
        }
        me->apply_condition("mj_shouwei", duration - 1);
        return 1;
}

string query_type(object me)
{
        return "job";
}