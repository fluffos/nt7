#include <ansi.h>

#define DIAN "「" HIW "鹤嘴劲点龙跃窍" NOR "」"

int exert(object me, object target)
{
        if( userp(me) && !query("can_perform/taiji-shengong/dian", me) )
                return notify_fail("你还没有领悟到这个运功诀窍，无法施展" DIAN "。\n"); 

        if (! target)
                return notify_fail("你要用真气为谁疗伤？\n");

        if (target == me)
                return notify_fail(DIAN "只能对别人施展。\n");

        if (me->is_fighting() || target->is_fighting())
                return notify_fail("战斗中无法运功疗伤。\n");

        if( query("not_living", target) )
                return notify_fail("你无法给" + target->name() + "疗伤。\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 100)
                return notify_fail("你的太极神功不够娴熟，难以施展" DIAN "。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的内力修为太浅，难以施展" DIAN "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你现在的真气不足，难以施展" DIAN "。\n");

        if( query("jing", me)<100 )
                return notify_fail("你现在精神状态不佳，难以施展" DIAN "。\n");

        if( query("eff_qi", target) >= query("max_qi", target) && 
            query("eff_jing", target) >= query("max_jing", target) )
                return notify_fail("对方没有受伤，不需要接受治疗。\n");

        message_sort(HIW "\n只见$N" HIW "双手食指和拇指虚拿，成鹤嘴劲"
                     "势，以食指指尖点在$n" HIW "耳尖三分处的龙跃窍，"
                     "运起内功，微微摆动。这招鹤嘴劲点龙跃窍使将出来，"
                     "便是新断气之人也能还魂片刻。过得一会便见得$p额头"
                     "上冒出豆大汗珠，头上冒出隐隐白雾，哇的一下吐出瘀"
                     "血，脸色登时看起来红润多了。\n" NOR, me, target);

        addn("neili", -800, me);
        me->receive_damage("qi", 100);
        me->receive_damage("jing", 50);

        target->receive_curing("qi", 100 + (int)me->query_skill("force") +
                                     (int)me->query_skill("taiji-shengong", 1) * 3);

        if( query("qi", target) <= 0 )
                set("qi", 1, target);

        target->receive_curing("jing", 100 + (int)me->query_skill("force") / 3 +
                                       (int)me->query_skill("taiji-shengong", 1));

        if( query("jing", target) <= 0 )
                set("jing", 1, target);

        if (! living(target))
                target->revive();

        if (! target->is_busy())
                target->stary_busy(2);

        message_vision("\n$N闭目冥坐，开始运功调息。\n", me);
        me->start_busy(10);
        return 1;
}
