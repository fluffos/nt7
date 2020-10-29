#include <ansi.h>
#include <combat.h>

#define DING "「" HIY "定岳七方" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, ap, dp;
        int count;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DING "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail("你所使用的武器不对，难以施展" DING "。\n");

        if ((int)me->query_skill("zhongping-qiang", 1) < 120)
                return notify_fail("你中平枪法不够娴熟，难以施展" DING "。\n");

        if (me->query_skill_mapped("club") != "zhongping-qiang")
                return notify_fail("你没有激发中平枪法，难以施展" DING "。\n");

        if ((int)me->query_skill("force") < 180 )
                return notify_fail("你的内功火候不够，难以施展" DING "。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的内力修为不够，难以施展" DING "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在的真气不够，难以施展" DING "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "身形一转，施出中平枪法绝技「" HIR "定岳七方"
              HIY "」，手中" + weapon->name() + HIY "接连七刺，枪枪不离"
             "$n" HIY "要害！\n" NOR;

        ap = attack_power(me, "club");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap * 2) > dp)
        {
                count = ap / 10;
                msg += HIR "$n" HIR "见$N" HIR "攻势凶猛异常，实非"
                       "寻常，不由心生寒意，招架登时散乱。\n" NOR;
        } else
        {
                count = 0;
                msg += HIC "$n" HIC "见$N" HIC "攻势凶猛异常，实非"
                       "寻常，急忙打起精神，小心应付开来。\n" NOR;
        }
        message_combatd(msg, me, target);

        addn("neili", -7*20, me);
        
        addn_temp("apply/attack", count, me);
        
        for (i = 0; i < 7; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(7));

        return 1;
}