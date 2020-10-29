// This program is a part of NITAN MudLIB
// 天涯明月刀「斩.绝」

#include <ansi.h>
#include <combat.h>

string name() { return HIY "斩"HIR"."HIY"诀" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if (me->query_skill("force") < 180)
                return notify_fail("你的内功的修为不够，难以施展" + name() + "。\n");

        if (me->query_skill("mingyue-blade", 1) < 120)
                return notify_fail("你的天涯明月刀修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<1200 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "mingyue-blade")
                return notify_fail("你没有激发天涯明月刀，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");


        msg= HIC "$N" HIC "心中涌起冲天豪气，就如驰骋沙场，杀将于千军万马之间的壮烈情怀，一声长啸，离地而起，疾若闪电般往$n掠去。\n"
             HIC "同时，手中" + weapon->name() + HIC"由横摆变成直指，强大和森寒彻骨的刀气朝$n狂涌而去。\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -240, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 210,
                                           HIR "$n" HIR "何曾见过如此高明的刀法，"
                                           "登时觉得眼前一片刀光，竟然不知如何躲避！\n" NOR);
                me->start_busy(2);
                if (ap / 3 + random(ap / 2) > dp && ! target->is_busy())
                        target->start_busy(3);
        } else
        {
                msg += CYN "$p" CYN "大吃一惊，也不招架，当即向后"
                       "横移数尺，避开了$P" CYN "这一招。\n" NOR;
                addn("neili", -120, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}

