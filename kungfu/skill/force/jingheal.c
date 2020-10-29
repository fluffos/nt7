// lifeheal.c

#include <ansi.h>

int exert(object me, object target)
{
        string force;

        if( !query("breakup", me) )
                return notify_fail("你还没有领悟利用真气激励精神的诀窍。\n");

        if (! target || target == me)
                return notify_fail("你要用真气为谁疗伤？\n");

        if (me->is_fighting() || target->is_fighting())
                return notify_fail("战斗中无法运功疗伤！\n");

        if( query("not_living", target) )
                return notify_fail("你不能给" + target->name() + "疗伤。\n");

        force = me->query_skill_mapped("force");
        if (! force)
                return notify_fail("你必须激发一种内功才能替人疗伤。\n");

        if ((int)me->query_skill(force,1) < 50)
                return notify_fail("你的" + to_chinese(force) + "等级不够。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的内力修为不够。\n");

        if( query("neili", me)<150 )
                return notify_fail("你现在的真气不够。\n");

        if( query("eff_jing", target) >= query("max_jing", target) )
                return notify_fail( target->name() +
                        "现在精力充沛，不需要你运功治疗！\n");

        if( query("eff_qi", target)<query("max_qi", target)/5 )
                return notify_fail( target->name() +
                        "已经受伤过重，经受不起你的真气震荡！\n");

        message_vision(
                HIY "$N坐了下来运起" + to_chinese(force) +
                "，将手掌贴在$n背心，缓缓地将真气输入$n体内....\n"
                HIW "过了不久，$N额头上冒出豆大的汗珠，$n吐出一"
                "口瘀血，缓缓睁开双目，精光四射。\n" NOR,
                me, target );

        //target->receive_curing("jing", 5 + (int)me->query_skill("force") / 6);
        target->receive_curing("jing", 5 + (int)me->query_skill("force"));
//        target->addn("qi", 10 + (int)me->query_skill("force") / 3);
        if( query("jing", target)>query("eff_jing", target) )
                set("jing",query("eff_jing",  target), target);

        addn("neili", -150, me);
        return 1;
}
