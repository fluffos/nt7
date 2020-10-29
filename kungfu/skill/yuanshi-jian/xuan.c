#include <ansi.h>
#include <combat.h>

#define XUAN "「" HIW "天旋地转" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if( userp(me) && !query("can_perform/yuanshi-jian/xuan", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XUAN "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" XUAN "。\n");

        if ((int)me->query_skill("yuanshi-jian", 1) < 180)
                return notify_fail("你的原始剑法不够娴熟，难以施展" XUAN "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你的真气不够，难以施展" XUAN "。\n");

        if (me->query_skill_mapped("sword") != "yuanshi-jian")
                return notify_fail("你没有激发原始剑法，难以施展" XUAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "一振手中" + weapon->name() + HIW "，挽出数朵剑花，层"
              "层涌向$n" HIW"，犹如潮水，一浪高过一浪。\n" NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("force");
        attack_time = 5;
        if (ap / 2 + random(ap * 2) > dp)
        {
                msg += HIR "$n" HIR "顿时只觉得头晕目眩，天旋地转，一时"
                       "难以招架。\n" NOR;
                count = ap / 16;
                addn_temp("apply/attack", count, me);
                attack_time += random(ap / 45);
        } else
        {
                msg += HIC "$n" HIC "见$N" HIC "剑势汹涌，急忙凝神抵挡"
                       "，不为所困。\n" NOR;
                count = 0;
        }
                
        message_combatd(msg, me, target);

        if (userp(me) && attack_time > 7)
                attack_time = 7;
              else if (attack_time > 21) 
                      attack_time = 21; 

        addn("neili", -attack_time*30, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(attack_time));

        return 1;
}
