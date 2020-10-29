#include <ansi.h>
inherit F_SSERVER;

string name() { return "刀影掌"; }

int perform(object me,object target)
{
        int j = me->query_skill("murong-daofa", 1);
        object weapon=query_temp("weapon", me);

        if( !target ) target = offensive_target(me);
        j = j * 2 / 3;
        if( !target || !me->is_fighting(target) )
                return notify_fail("刀影掌只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("zihui-xinfa", 1) < 100 )
                return notify_fail("你的内功还未练成，不能使用刀影掌！\n");

        if( (int)me->query_skill("murong-daofa", 1) < 100 )
                return notify_fail("你的刀法还未练成，不能使用刀影掌！\n");

        if( !weapon || query("skill_type", weapon) != "blade"
        || me->query_skill_mapped("blade") != "murong-daofa")
                return notify_fail("你手里没有刀，无法使用刀影掌！\n");

        if((int)me->query_skill("xingyi-zhang", 1) < 100 )
                return notify_fail("你的掌法还未练成，不能使用刀影掌！\n");

        if(me->query_skill_mapped("force") != "zihui-xinfa")
                return notify_fail("你的内功不是神元功，无法使用刀影掌！\n");

        if(me->query_skill_mapped("strike") != "xingyi-zhang" ||
           me->query_skill_prepared("strike") != "xingyi-zhang")
                return notify_fail("你没有用掌，无法使用刀影掌！\n");

        if(me->query_skill_mapped("parry") != "xingyi-zhang")
                if(me->query_skill_mapped("parry") != "murong-daofa")
                       return notify_fail("你的招架功夫不对，无法使用刀影掌！\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你现在内力修为不够，不能使用刀影掌！\n");

        if( query("neili", me)<600 )
                return notify_fail("你现在内力不足，不能使用刀影掌！\n");

        if((int)me->query_skill("blade", 1) < 100 )
                return notify_fail("你的基本刀法不够娴熟，不能在刀招中夹杂使用刀影掌。\n");

        if((int)me->query_skill("strike", 1) < 100 )
                return notify_fail("你的基本掌法不够娴熟，不能在刀招中夹杂使用刀影掌。\n");

        message_combatd(HIR"\n$N大吼一声使出慕容绝技「刀影掌」，只见$P掌随刀走，片片刀光中夹杂着阵阵掌风一起奔向$n！\n"NOR, me,target);
        addn("neili", -200, me);
        addn_temp("apply/attack", j, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
        weapon->unequip();
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
        weapon->wield();
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
        if ((int)me->query_str() > 30)
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
        addn_temp("apply/attack", -j, me);
        me->start_busy(2+random(2));
        return 1;
}
