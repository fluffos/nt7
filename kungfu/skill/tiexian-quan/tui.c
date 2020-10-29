#include <ansi.h>
#include <combat.h>

string name() { return HIW "破甲推山" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("tiexian-quan", 1) < 60)
                return notify_fail("你铁线拳法不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("cuff") != "tiexian-quan")
                return notify_fail("你没有激发铁线拳法，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "tiexian-quan")
                return notify_fail("你没有准备铁线拳法，难以施展" + name() + "。\n");

        if (me->query_skill("force") < 80)
                return notify_fail("你的内功修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "parry");

        msg = HIC "\n$N" HIC "长啸一声，施出绝招「" HIW "开山破" HIC "」，一\n"
              "拳挥出，破空而响，直击$n" HIC "面门和胸口。\n" NOR;

        message_combatd(msg, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "cuff");

                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                          HIR "$N" HIR "出手既快，方位又奇，$n"
                                          HIR "闪避不及，闷哼一声，已然中拳。\n" NOR);

                addn("neili", -100, me);
                me->start_busy(2);
        } else
        {
                msg = CYN "$n" CYN "不慌不忙，以快打快，将$N"
                      CYN "这招化去。\n" NOR;

                addn("neili", -30, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}