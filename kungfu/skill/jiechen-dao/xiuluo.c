// by snowman

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
      int i, jiali, count;
        string msg;
       object weapon;

       if( !target ) target = offensive_target(me);
       if( !target
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target))
                return notify_fail("「修罗焰」攻击只能对战斗中的对手使用。\n");

      if( !objectp(weapon=query_temp("weapon", me)) || 
          query("skill_type", weapon) != "blade" )
                return notify_fail("你先找把刀再说吧！\n");


        if (me->query_skill_mapped("blade") != "jiechen-dao")
                return notify_fail("你必须使用戒尘刀来施展「修罗焰」。\n");

        if(me->query_skill("jiechen-dao", 1) < 180 )
                return notify_fail("你的戒尘刀火候还嫌不够，这「修罗焰」绝技不用也罢。\n");

        if(me->query_skill("blade", 1) < 180 )
                return notify_fail("你的基本刀法还不够娴熟，使不出「修罗焰」绝技。\n");

        if( (int)me->query_skill("hunyuan-yiqi", 1) < 140 )
                return notify_fail("你的心意气混元功等级不够，使不出「修罗焰」绝技。\n");

        if( (int)me->query_con() < 34)
                return notify_fail("你的身体还不够强壮，强使「修罗焰」绝技是引火自焚！\n");

        if ( me->query_skill_mapped("force") != "hunyuan-yiqi")
           return notify_fail("你现在这内功平平无奇，如何使得出「修罗焰」绝技来！？\n"); 

        if( query("max_neili", me)<3000 )
           return notify_fail("你的内力修为不够，这「修罗焰」绝技不用也罢。\n");

        if( query("neili", me)<1000 )
           return notify_fail("以你目前的内力来看，这「修罗焰」绝技不用也罢。\n");

        addn("neili", -300, me);
 
        message_vision(HIR "\n突然$N将手中武器从右手交到左手，运出十二分真力，脸色顿时通红，\n"
                           "宛如修罗降世。刀刃在内力的催动下立刻攻势大胜，\n"
                           "向着$n直劈而下！\n" NOR, me, target);      

        i = me->query_skill("force") / 2 * (3+random(4));        
        jiali=query("jiali", me);

        set("jiali", i, me);
        addn_temp("apply/attack", jiali/2, me);
        
        count = 4;
        count += random(4);
        while (count --)
        {

              COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
        }
        
        addn_temp("apply/attack", -jiali/2, me);
        set("jiali", jiali, me);
        if( !query_temp("xiuluo", me))addn("neili", -300, me);
        else delete_temp("xiuluo", me);

        me->start_busy(1+random(3));
        return 1;
}
