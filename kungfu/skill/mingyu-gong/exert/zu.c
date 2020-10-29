// zu.c  by sinb

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用明玉功恢复自己的气血。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的真气不够！\n");

        if (me->query_condition("mingyu_qizu"))
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("mingyu-gong", 1);

        addn("neili", -100, me);

        message_combatd(HIC "$N" HIC "运起「气足」奇功，"
                        "眼中闪过一片青芒，随即恢复正常\n" NOR, me);


        me->apply_condition("mingyu_qizu", skill / 100);
        if (me->is_fighting()) me->start_busy(3);

        return 1;
}
