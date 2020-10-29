// sangong.c

#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        if( query("max_neili", me)<1 )
                return notify_fail("你已经将内力散尽，没什么必要再散功了。\n");

        tell_object(target, HIY "你默默的按照吸星大法的诀窍将内力散入奇经八脉。\n" NOR);
        message("vision", HIY + me->name() + "呼吸沉重，却又不像受伤的样"
                          "子，不知道在修炼什么厉害的功夫。\n" NOR,
                environment(me), ({ me }));

        me->start_busy(1);
        addn("max_neili", -100, me);
        if( query("max_neili", me)<0 )
                set("max_neili", 0, me);

        if( query("max_neili", me) < 1 )
        {
                set("can_learn/xixing-dafa/ren", 1, me);
                tell_object(me, HIR "你终于悟得学习吸星大法，压抑内力反噬的方法。\n" NOR);
        }
        return 1;
}

void del_sucked(object me)
{
        delete_temp("sucked", me);
}
