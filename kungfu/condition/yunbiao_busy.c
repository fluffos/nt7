// yunbiao_busy.c

#include <ansi.h>

string chinese_name() { return "运镖失败"; }
int update_condition(object me, int duration)
{
        if( duration <= 1 )
        {
                delete_temp("quest_yunbiao", me);
                tell_object(me, HIR "你可以回去领取运镖任务了。\n" NOR);
                return 0;
        }
        me->apply_condition("yunbiao_busy", duration - 1);
        return 1;
}

string query_type(object me)
{
        return "job";
}
