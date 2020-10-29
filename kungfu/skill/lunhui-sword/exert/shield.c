
#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用六道轮回剑来提升自己的战斗力。\n");

        if( query_temp("shield", me) )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        message_combatd(HIR "$N" HIR "暗运六道轮回真气，须臾，只见天边云开雾去，流光溢彩，一把气剑奔射而出，围绕在$N" HIR "四周。\n" NOR, me);

        // 打通BREAKUP后的效果增加10%
        if( query("breakup", me))skill=skill+skill*1/10;
                
        addn_temp("apply/armor", skill/2, me);
        addn_temp("apply/parry", skill/10, me);
        set_temp("shield", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill :), skill / 2);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (! objectp(me))return;

        if( query_temp("shield", me) )
        {
                addn_temp("apply/armor", -(amount/2), me);
                addn_temp("apply/parry", -(amount/10), me);

                delete_temp("shield", me);
                tell_object(me, HIW "你的六道轮回剑「神剑护体」运行完毕，将内力收回丹田。\n" NOR);
        }


}