// This program is a part of NITAN MudLIB

#include <ansi.h>

#define HEAL "「" HIR "起死回生" NOR "」"

int exert(object me, object target)
{
        string force;

        if( userp(me) && !query("can_exert/yijin-duangu/heal", me) )
                return notify_fail("你所学的内功中没有这种功能。\n");

        if (! target)
                return notify_fail("你要用真气为谁疗伤？\n");

        if (target == me)
                return notify_fail(HEAL "只能对别人施展。\n");

        if (me->is_fighting() || target->is_fighting())
                return notify_fail("战斗中无法运功疗伤。\n");

        if( query("not_living", target) )
                return notify_fail("你无法给" + target->name() + "疗伤。\n");

        if ((int)me->query_skill("yijin-duangu", 1) < 100)
                return notify_fail("你的易筋锻骨不够娴熟，难以施展" HEAL "。\n");

        if (me->query_skill_mapped("force") != "yijin-duangu")
                return notify_fail("你没有激发易筋锻骨，难以施展" HEAL "。\n");
                
        if( query("max_neili", me)<1500 )
                return notify_fail("你的内力修为太浅，难以施展" HEAL "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你现在的真气不足，难以施展" HEAL "。\n");

        if( query("jing", me)<100 )
                return notify_fail("你现在的状态不佳，难以施展" HEAL "。\n");

        if( query("eff_qi", target) >= query("max_qi", target) && 
            query("eff_jing", target) >= query("max_jing", target) )
                return notify_fail("对方没有受伤，不需要接受治疗。\n");

        message_sort(HIY "\n只见$N" HIY "默默运转" + to_chinese(force) +
                     HIY "，深深吸进一口气，头上隐隐冒出白雾，陡然施展开"
                     "易筋锻骨，以纯阴内力瞬时点遍了$n" HIY "全身七十二"
                     "处大穴。过得一会，便见得$n" HIY "“哇”的一下吐出"
                     "几口瘀血，脸色登时看起来红润多了。\n" NOR, me, target);

        addn("neili", -800, me);
        me->receive_damage("qi", 100);
        me->receive_damage("jing", 50);

        target->receive_curing("qi", 100 + (int)me->query_skill("force") +
                                     (int)me->query_skill("yijin-duangu", 1) * 3);

        if( query("qi", target) <= 0 )
                set("qi", 1, target);

        target->receive_curing("jing", 100 + (int)me->query_skill("force") / 3 +
                                       (int)me->query_skill("yijin-duangu", 1));

        if( query("jing", target) <= 0 )
                set("jing", 1, target);

        if ((int)target->query_condition("hamagong_poison"))
        {
                target->clear_condition("hamagong_poison");
                tell_object(target, HIC "\n你只觉体内残存的蛤蟆功伤慢慢"
                                    "消退，感觉好多了。\n" NOR);
        }

        if (! living(target))
                target->revive();

        if (! target->is_busy())
                target->stary_busy(2);

        message_vision("\n$N闭目冥坐，开始运功调息。\n", me);
        me->start_busy(10);
        return 1;
}