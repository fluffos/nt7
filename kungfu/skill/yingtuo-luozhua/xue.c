#include <ansi.h>
#include <combat.h>

#define JU "「" HIR "赤血爪" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JU "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(JU "只能空手施展。\n");

        if ((int)me->query_skill("yingtuo-luozhua", 1) < 200)
                return notify_fail("你因陀罗爪不够娴熟，难以施展" JU "。\n");

        if (me->query_skill_mapped("claw") != "yingtuo-luozhua")
                return notify_fail("你没有激发因陀罗爪，难以施展" JU "。\n");

        if (me->query_skill_prepared("claw") != "yingtuo-luozhua")
                return notify_fail("你没有准备因陀罗爪，难以施展" JU "。\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够，难以施展" JU "。\n");

        if( query("neili", me)<420 )
                return notify_fail("你现在的真气不够，难以施展" JU "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap=me->query_skill("claw")+query("force", me);
        dp=target->query_skill("parry")+query("force", target);

        msg = HIW "\n$N" HIW "运转真气，双手忽成爪行，施出绝招「" HIR "赤"
              "血爪" HIW "」，迅猛无比地抓向$n" HIW "。\n" NOR;

        if (ap * 3 / 4 + random(ap) > dp)
        {
                damage = ap + random(ap);
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
                                           HIR "但见$N" HIR "双爪划过，$n" HIR "已闪避不及，胸口被$N" HIR
                                           "抓出十条血痕。\n" NOR);

                me->start_busy(2);
                addn("neili", -400, me);
        } else
        {
                msg += CYN "$n" CYN "奋力招架，竟将$N" CYN "这招化解。\n" NOR;

                me->start_busy(2);
                addn("neili", -200, me);
        }
        message_sort(msg, me, target);
        return 1;
}