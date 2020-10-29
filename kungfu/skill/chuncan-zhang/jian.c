#include <ansi.h>

#define JIAN "「" HIW "作茧自缚" NOR "」"

inherit F_CLEAN_UP;
inherit F_SSERVER;

void remove_effect(object me, int a_amount, int d_amount);

int perform(object me)
{
        object weapon;
        int skill;
        string msg;

        if( userp(me) && !query("can_perform/chuncan-zhang/jian", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if( query_temp("ccz_jian", me) )
                return notify_fail("你已经运起" JIAN "了。\n");

        if ((int)me->query_skill("chuncan-zhang", 1) < 80)
                return notify_fail("你的春蚕掌法不够娴熟，难以施展" JIAN "。\n");

        if ((int)me->query_skill("force", 1) < 120)
                return notify_fail("你的内功火候不够，难以施展" JIAN "。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的内力修为不够，难以施展" JIAN "。\n");

        if (me->query_skill_mapped("strike") != "chuncan-zhang")
                return notify_fail("你没有激发春蚕掌法，难以施展" JIAN "。\n");

        if (me->query_skill_prepared("strike") != "chuncan-zhang")
                return notify_fail("你没有准备春蚕掌法，难以施展" JIAN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，难以施展" JIAN "。\n");

        msg = HIW "$N" HIW "凝聚内力，掌劲吞吐，顿时双掌掀起一层气劲，护住周身经脉。\n\n" NOR;
        message_combatd(msg, me);

        skill = me->query_skill("chuncan-zhang", 1);

        addn_temp("apply/attack", -skill/4, me);
        addn_temp("apply/dodge", skill/3, me);
        set_temp("ccz_jian", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 4, skill / 3 :), skill / 2);

        addn("neili", -150, me);
        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int a_amount, int d_amount)
{
        if( query_temp("ccz_jian", me) )
        {
                addn_temp("apply/attack", a_amount, me);
                addn_temp("apply/dodge", -d_amount, me);
                delete_temp("ccz_jian", me);
                tell_object(me, "你的" JIAN "运行完毕，将内力收回丹田。\n");
        }
}