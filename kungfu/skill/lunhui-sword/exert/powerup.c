#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用六道轮回剑来提升自己的战斗力。\n");

        if( query_temp("powerup", me) )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        message_combatd(HIG "\n$N" HIG "长叹一声，手挽宝剑，谈笑风声间，六道真气自体内而出，涌向天际，化作一朵金兰，消失了。\n" NOR, me);

        // 打通BREAKUP后的效果增加20%
        if( query("breakup", me))skill=skill+skill*2/10;

        addn_temp("apply/attack", skill, me);
        addn_temp("apply/damage", skill, me);

        set_temp("powerup", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill :), skill / 2);
      
        return 1;
}

void remove_effect(object me, int amount)
{
        if (! objectp(me))return;
                                
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/damage", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, HIY "你的六道轮回剑「剑气通天」运行完毕，将内力收回丹田。\n" NOR);
        }


}