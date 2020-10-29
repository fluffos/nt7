#include <ansi.h>
#include <combat.h>

string name() { return HIC "风云变幻" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int count, ap, dp;
        int lvl;
        int i;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((lvl = (int)me->query_skill("wuluo-zhang", 1)) < 100)
                return notify_fail("你五罗轻烟掌不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "wuluo-zhang")
                return notify_fail("你没有激发五罗轻烟掌，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "wuluo-zhang")
                return notify_fail("你没有准备五罗轻烟掌，难以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "施出五罗轻烟掌绝技，单掌轻轻一抖，登时化出五道掌"
              "影，轻飘飘向$n" HIC "拍去。\n" NOR;
        addn("neili", -50, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "顿时觉得眼花缭乱，全然分辨"
                       "不清真伪，只得拼命运动抵挡。\n" NOR;
                count = lvl / 10;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "可是$n" HIC "凝神顿气，奋力抵挡，丝"
                       "毫不受掌影的干扰，。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->start_busy(1 + random(4));
        addn_temp("apply/attack", -count, me);
        return 1;
}