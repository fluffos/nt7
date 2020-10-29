// yijin.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int skill);

int exert(object me, object target)
{
        int skill, n;

        if (target != me)
                notify_fail("你只能对自己用["+WHT+"易经转脉"+NOR+"]来提升自已的战斗和防御力。\n"NOR,);

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够!");
        if( userp(me) && !query("can_perform/jiuyin-hamagong/yijin", me) )
                      return notify_fail("你所使用的外功中没有这种功能。\n"); 

        if( query_temp("yijin", me) )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        n = skill / 5;

        addn("neili", -400, me);
        me->receive_damage("qi", 0);

        message_combatd(HIY "$N" HIY "深深吸了一口气。突然双掌撑地，双脚朝上，只"
                        "见全身衣物逐渐膨涨起来，口中不停蛙呜，脸色忽红忽紫！\n" NOR, me);

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/defense", skill/3, me);
        addn_temp("apply/dodge", skill/3, me);
        addn_temp("apply/parry", skill/3, me);
        addn_temp("apply/armor", skill/3, me);
                addn_temp("apply/damage", skill/2, me);
        addn_temp("apply/dispel_poison", skill/3, me);
        addn_temp("apply/reduce_poison", 15, me);//提高15%的抗毒

        set_temp("yijin", skill, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, skill :), n);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int skill)
{
        skill=query_temp("yijin", me);
        
        if( query_temp("yijin", me) )
        {
                addn_temp("apply/attack", -(skill/3), me);
                addn_temp("apply/defense", -(skill/3), me);
                addn_temp("apply/dodge", -(skill/3), me);
                addn_temp("apply/parry", -(skill/3), me);
                addn_temp("apply/armor", -(skill/3), me);
                addn_temp("apply/damage", -(skill/2), me);
                addn_temp("apply/dispel_poison", -(skill/3), me);
                addn_temp("apply/reduce_poison", -15, me);
                delete_temp("yijin", me);
                tell_object(me, "你的["+HIR+"易经转脉"+NOR+"]运行完毕，将内力收回丹田。\n");
        }
}

