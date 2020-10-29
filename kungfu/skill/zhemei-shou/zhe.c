// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIC "折梅式" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon, weapon2;
        int skill, ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail(name() + "只能空手施展。\n");

        skill = me->query_skill("zhemei-shou", 1);

        if (skill < 80)
                return notify_fail("你的折梅手等级不够，难以施展" + name() + "。\n");

        if (me->query_skill("force") < 120)
                return notify_fail("你内功火候不够，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在真气不足，难以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "合逍遥折梅手诸多变化为一式，随手轻轻挥出，虚虚"
              "实实笼罩$n" HIC "全身诸处要穴。\n" NOR;

        ap = attack_power(me, "hand");
        dp = defense_power(target, "parry");

        addn("neili", -80, me);
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -50, me);
                msg += HIR "$n" HIR "心头一颤，想不出破解之法，急忙后"
                      "退数步，一时间无法反击。\n" NOR;
                target->start_busy(ap / 90 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "的看破了$P" CYN "的企图，丝"
                      "毫不为所动，让$P" CYN "的虚招没有起得任何作用。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}