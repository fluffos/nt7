#include <ansi.h>
#include <combat.h>

#define ZHEN "「" HIR "震雷乾坤" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, ap, dp, count;

        if( userp(me) && !query("can_perform/qujing-gunfa/zhen", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHEN "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不对，难以施展" ZHEN "。\n");

        if (me->query_skill_mapped("club") != "qujing-gunfa")
                return notify_fail("你没有激发取经棍法，难以施展" ZHEN "。\n");

        if(me->query_skill("qujing-gunfa", 1) < 200 )
                return notify_fail("你取经棍法不够娴熟，难以施展" ZHEN "。\n");

        if( (int)me->query_skill("force") < 350 )
                return notify_fail("你的内功修为不够，难以施展" ZHEN "。\n");

        if( query("max_neili", me)<4500 )
                return notify_fail("你的内力修为太弱，难以施展" ZHEN "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气太弱，难以施展" ZHEN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "将手中" + weapon->name() + HIW "缓缓压向$n"
              HIW "，棍体隐隐带着风雷之劲，正是取经棍法杀着「" HIR "震"
              "雷乾坤" HIW "」！\n电光火石间，棍端竟全被紫电所笼罩，" +
              weapon->name() + HIW "幻作千百根相似，奔雷掣电般向$n" HIW
              "席卷而去。\n" NOR;

        ap = me->query_skill("club");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap * 2) > dp)
        {
                msg += HIR "$n" HIR "被$N" HIR "气势所撼，完全不知该如"
                       "何招架，竟而呆立当场！\n" NOR;
                count = ap / 8;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "见$N" HIC "气势如虹，心下凛然，急"
                       "忙凝神聚气，小心应付！\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        addn("neili", -200, me);

        for (i = 0; i < 10; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(9));
        return 1;
}
