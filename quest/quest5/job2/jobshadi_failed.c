// dart_limit.c

#include <login.h>

int update_condition(object me, int duration)
{
        if (duration < 1) return 0;
        me->apply_condition("jobshadi_failed", duration - 1);
        return 1;
}