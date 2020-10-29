// This program is a part of NITAN MudLIB

#include <ansi.h>

string name() { return MAG "移星换月" NOR; }

void remove_effect(object me);

int perform(object me, object target)
{
        string msg;
        int level;

        if( (level = me->query_skill("douzhuan-xingyi", 1)) < 1000 )
                return notify_fail("你的斗转星移还不够熟练，难以施展" + name() + "。\n" NOR);

        if( (int)query("jingli", me) < 2000 )
                return notify_fail("你现在真气不足，难以施展" + name() + "。\n" NOR);

        if( (int)query("neili", me) < 5000 )
                return notify_fail("你现在内力不够，难以施展" + name() + "。\n" NOR);

        if (query_temp("yixinghuanyue", me))
                return notify_fail("你已经运起" + name() + "。\n" NOR);

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);
        set_temp("yixinghuanyue", 1, me);
        msg = MAG "\n$N" MAG "提起真气，默念" + name() + "心法，心中以彼之道还彼之身的法门已达发乎自然之境。\n" NOR;

        message_combatd(msg, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), level);

        if( me->is_fighting() ) me->start_busy(2);
        return 1;

}

void remove_effect(object me)
{
        if ((int)query_temp("yixinghuanyue", me))
        {
                delete_temp("yixinghuanyue", me);
                tell_object(me, "你的"+name()+"运功完毕，将内力收回丹田。\n");
        }
}

