//kuang.c 
// gladiator

#include <ansi.h>
#include <combat.h>

#define KUANG "「" HIR "狂风落叶" NOR "」" 

inherit F_SSERVER;

int perform(object me, object target)
{
        int extra;
        object weapon;
        string msg;

        extra=me->query_skill("hongye-daofa",1);

        if( userp(me) && !query("can_perform/hongye-daofa/kuang", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if( !target ) target = offensive_target(me);

        if( !target||!target->is_character()||!me->is_fighting(target) )
                return notify_fail("你只能对战斗中的对手使用" KUANG "。\n");

        if( (int)me->query_skill("hongye-daofa",1) < 150)
                return notify_fail("你目前功力还使不出" KUANG "。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "blade" )
                        return notify_fail("你使用的武器不对。\n");

        if( query("neili", me)<800 )
                        return notify_fail("你的内力不够。\n");
  if (! living(target)) 
         return notify_fail("对方都已经这样了，用不着这么费力吧？\n"); 

        addn("neili", -300, me);
        msg = HIC "$N淡然一笑，本就快捷绝伦的刀法骤然变得更加凌厉！\n"
              HIC "就在这一瞬之间，$N已劈出二十一刀！刀夹杂着风，风里含着刀影！\n"
              HIC "$n只觉得心跳都停止了！" NOR;

        message_vision(msg, me, target);                
        
        message_combatd(HIY  "$N从左面劈出七刀！" NOR, me, target); 
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);

        message_combatd(HIY  "$N紧跟$n从右面劈出七刀！" NOR, me, target); 
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);

        message_combatd(HIY  "$N竟然又从上面劈出七刀！" NOR, me, target);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);

        me->start_busy(2 + random(2));
        return 1;
}