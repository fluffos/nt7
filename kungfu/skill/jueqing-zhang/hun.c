#include <ansi.h>
#include <combat.h>

#define HUN "「" HIM "魂飞魄散" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUN "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(HUN "只能空手施展。\n");

        if ((int)me->query_skill("jueqing-zhang", 1) < 140)
                return notify_fail("你绝情掌不够娴熟，难以施展" HUN "。\n");

        if (me->query_skill_mapped("strike") != "jueqing-zhang")
                return notify_fail("你没有激发绝情掌，难以施展" HUN "。\n");

        if (me->query_skill_prepared("strike") != "jueqing-zhang")
                return notify_fail("你没有准备绝情掌，难以施展" HUN "。\n");

        if (me->query_skill("force") < 180)
                return notify_fail("你的内功修为不够，难以施展" HUN "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不够，难以施展" HUN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        msg = HIC "\n$N" HIC "运转真气，将内力注于掌风之中，双掌猛"
              "然拍向$n" HIC "，掌风凌厉无比，气势凌人，直可惊天"
              "地，泣鬼神，正是绝情谷绝学「" HIM "魂飞魄散" HIC "」。"
              "\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "但见$N" HIR "双掌拍来，掌风作响，"
                                           "当真气势凌人。$n" HIR "顿觉心惊胆战，"
                                           "毫无招架之力，微迟疑间$N" HIR "这掌"
                                           "已正中$n" HIR "胸口，顿将$p震退数步。"
                                           " \n" NOR);

                me->start_busy(2);
                addn("neili", -200, me);
        } else
        {
                msg += CYN "$n" CYN "见$N" CYN "这掌拍来，内力"
                       "充盈，气势凌人，只得奋力向后一纵，才躲"
                       "过这一掌。\n" NOR;

                me->start_busy(3);
                addn("neili", -100, me);
        }
        message_sort(msg, me, target);
        return 1;
}