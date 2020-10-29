#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{   
        if (duration == 1)
        {
                tell_object(me, HIR "你一个月没有继续化毒，体内毒力已经开始渐渐不受控制！\n" NOR );
                message("vision", me->name() +"的身体一震，神色发散，脸色开始发青。\n", environment(me), me);
                me->apply_condition("hua_poison", 80 + me->query_skill("huagong-dafa", 1));
        }
        me->apply_condition("hua_du", duration - 1);

        if (duration < 1) return 0;
        return CND_CONTINUE;
}