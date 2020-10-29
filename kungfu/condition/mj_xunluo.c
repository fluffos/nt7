// mj_xunluo.c 

#include <login.h>
#include <ansi.h>
int update_condition(object me, int duration)
{
        if (duration < 1) { 
              delete_temp("mj/attacker1", me);
              delete_temp("mj/over", me);
              delete_temp("mj/xunluo", me);
              me->clear_condition("mj_xunluo");
        }
        if (!duration) return 0;
        me->apply_condition("mj_xunluo", duration - 1);
        return 1;
}