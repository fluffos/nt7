// powerup.c 惊神诀提升战斗力
// By Alf, Last Update 2001.10

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
    int skill;

    if( target != me ) 
        return notify_fail("你只能用惊神诀来提升自己的战斗力。\n");

    if( query("neili", me)<100 )
        return notify_fail("你的内力不够。\n");
    if( query_temp("powerup", me) )
        return notify_fail("你已经在运功中了。\n");

    skill = me->query_skill("force");
    addn("neili", -100, me);

    message_vision(
    HIC "$N淡淡一笑间，内息已暗自流转不绝，身周犹如多了一道无形屏障。\n" NOR, me);

    addn_temp("apply/attack", skill/3, me);
    addn_temp("apply/dodge", skill/3, me);
    set_temp("powerup", 1, me);

    me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill/3 :), skill);

    if( me->is_fighting() ) me->start_busy(3);

    return 1;
}

void remove_effect(object me, int amount)
{
   if( query_temp("powerup", me)){
    addn_temp("apply/attack", -amount, me);
    addn_temp("apply/dodge", -amount, me);
    delete_temp("powerup", me);
    tell_object(me, "你的惊神诀运行完毕，将内力收回丹田。\n");}
}

