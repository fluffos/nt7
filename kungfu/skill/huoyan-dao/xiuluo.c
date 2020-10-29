 // 修罗降世 xiuluo.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "修罗降世"; }

int perform(object me, object target)
{
      object weapon;

      int i, jiali;
      string msg;

       if( !target ) target = offensive_target(me);
       if( !target
       ||  !target->is_character()
       ||  !me->is_fighting(target)
       ||  !living(target))
                return notify_fail("「修罗降世」攻击只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("「修罗降世」是空手绝技，你拿着武器是使不出来的！\n");

        if( me->query_skill_mapped("strike") != "huoyan-dao" )
                return notify_fail("你必须使用火焰刀来施展「修罗降世」。\n");

        if( me->query_skill("huoyan-dao", 1) < 150 )
                return notify_fail("你的火焰刀火候还嫌不够，这「修罗降世」绝技不用也罢。\n");

        if( me->query_skill("strike", 1) < 150 )
                return notify_fail("你的基本掌法还不够娴熟，使不出「修罗降世」绝技。\n");

        if( userp(me) && (int)me->query_skill("xiaowuxiang", 1) < 100 )
                return notify_fail("你的小无相功等级不够高，使不出「修罗降世」。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的内力修为不够，这「修罗降世」绝技不用也罢。\n");

        if( query("neili", me)<500 )
                return notify_fail("以你目前的内力来看，这「修罗降世」绝技不用也罢。\n");

        if( query("jing", me)<80 )
                return notify_fail("你的精力不够。\n");



        addn("jing", -20, me);
        msg =HIR "突然" HIR "$N" HIR "双掌搓了几搓，只听得嗤嗤声响，「火焰刀」在" HIR "$N" HIR "极强内劲的斗然冲击之下\n"
             HIR "威势大盛，激射而出的无形刀气组成了一片刀网，宛如修罗降世，向着" HIR "$n" HIR "直劈而下! \n" NOR;

        message_combatd(msg,me,target);
        i = me->query_skill("force") / 4;
        jiali=query("jiali", me);

        set("jiali", i, me);
        addn_temp("apply/attack", jiali+200, me);
        addn_temp("apply/unarmed_damage", jiali+200, me);
        msg = HIY"\n\n刀山火海！\n\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);



        msg = HIR"------无尽炼狱！\n\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);



        msg = RED"--------------四方俱灭！\n\n"NOR;
        message_combatd(msg,me,target);
        COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);



        addn_temp("apply/attack", -jiali-200, me);
        addn_temp("apply/unarmed_damage", -jiali-200, me);
        me->start_busy(1+random(2));
        return 1;
}
