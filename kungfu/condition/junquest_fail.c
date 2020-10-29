// junquest_fail

#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{      
        if( duration < 1 ) return 0;
        
        me->apply_condition("junquest_fail", duration - 1); 

        if( duration == 1)
        {
                tell_object(me, HIR "朝廷招你回去，快回京师接旨吧！！！\n" NOR);
        }
        
        return CND_CONTINUE;      
}
