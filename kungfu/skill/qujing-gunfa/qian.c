#include <ansi.h>
#include <combat.h>

#define TUN "「" HIR "乾天无极" NOR "」"

inherit F_SSERVER;

void remove_effect(object me, int skill);

int perform(object me, object target)
{
        object weapon;
        int skill;
        string msg;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail(TUN "你必须用棍法施展。\n");

        if( query_temp("qujing_qian", me) )
                return notify_fail(TUN "无法连续施展。\n");

        if ((int)me->query_skill("qujing-gunfa", 1) < 180)
                return notify_fail("你的乾天无极修为不够，难以施展" TUN "。\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("你的内力修为不足，难以施展" TUN "。\n");

        if (me->query_skill_mapped("club") != "qujing-gunfa")

                return notify_fail("你没有激发取经棍法为棍法，难以施展" TUN "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在的真气不足，难以施展" TUN "。\n");


        msg = HIY "$N" HIY "双手持刀，对天咆哮，所施正是乾天无极绝学「"
              HIR "乾天无极" HIY "」。\n霎时呼啸声大作，但见一股澎湃无比的罡劲"
              "至$N" HIY "刀间涌出，云贯向$N" HIY "而去。\n" NOR;
        message_sort(msg, me);
        if (me->is_fighting())
                me->start_busy(2);
        skill = me->query_skill("qujing-gunfa",1);
        set_temp("qujing_qian", 1, me);
        addn_temp("apply/attack", skill*3/5, me);
        addn_temp("apply/defense", skill*2/5, me);
        addn_temp("apply/weapon_damage", skill/3, me);
        addn("neili", -600, me);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill);
        return 1;
}

void remove_effect(object me, int skill)
{
        if( query_temp("qujing_qian", me) )
        {
                addn_temp("apply/attack", -(skill*3/5), me);
                addn_temp("apply/defense", -(skill*2/5), me);
                addn_temp("apply/weapon_damage", -(skill/3), me);
                delete_temp("qujing_qian", me);
                tell_object(me, "你经过调气养息，又可以继续施展「" HIR "乾天无极" NOR "」了。\n");
        }
}

