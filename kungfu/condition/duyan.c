#include <ansi.h>

int update_condition(object me, int duration)
{
        int dam;

        if (query("neili", me) >= 4000)
                dam = random(50);
        else

        if (query("neili", me) > 3000)
                dam = random(500);
        else

        if (query("neili", me) > 2000)
                dam = random(1000);
        else

        if (query("neili", me) > 1000)
                dam = random(1500);
        else

        if (query("neili", me) > 500)
                dam = random(2000);
        else
                dam = random(3000);

        me->receive_wound("qi", dam);
        me->receive_wound("jing", dam);
        me->apply_condition("duyan", duration - 1);

        if (duration < 1)
                tell_object(me, HIW "你中的毒盐终于发作光了。\n" NOR );
        else
                tell_object(me, HIW "你中的毒盐发作了！\n" NOR );

        if (duration < 1)
                return 0;

        return 1;
}