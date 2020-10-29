// powerup.c
// Last Modified by Lonely on Mar. 10 2000

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

  if ( userp(me) && !wizardp(me) && 
  !query("perform/powerup", me) && 
  !query("can_perform/dulong-dafa/powerup", me) && 
  !query_temp("murong/xingyi", me) )
   return notify_fail("你所使用的内功中没有这种功能。");

        if(target != me)
                return notify_fail("你只能用毒龙大法提升自己的战斗力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够!");
        if( query_temp("powerup", me) )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
                me->receive_damage("qi", 0);

        message_combatd(
        HIM "$N舌尖一咬，喷出一口紫血，顿时一股内力直贯双臂！\n" NOR, me);

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/dodge", skill/3, me);
        set_temp("powerup", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill/3 :), skill);

        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/dodge", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, "你的毒龙大法运行完毕，将内力收回丹田。\n");
        }
}
int help(object me)
{
        write(WHT"\n毒龙大法之加力："NOR"\n");
        write(@HELP

        使用功效：
                提升自己的攻击防御能力

        出手要求：
                内力100
HELP
        );
        return 1;
}
