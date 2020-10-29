// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "排山倒海" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手使用。\n");

        if ((int)me->query_skill("dragon-strike", 1) < 150)
                return notify_fail("你降龙十八掌火候不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "dragon-strike")
                return notify_fail("你没有激发降龙十八掌，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "dragon-strike")
                return notify_fail("你没有准备降龙十八掌，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的内力修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = WHT "$N" WHT "施出降龙十八掌之「" HIW "排山倒海" NOR +
              WHT "」，全身真气鼓动，双掌如排山倒海般压向$n" WHT "。\n"NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 85,
                                           HIR "$n" HIR "只觉一股罡风涌至，根本不"
                                           "及躲避，$N" HIR "双掌正中前胸，鲜血如"
                                           "箭般喷出。\n" NOR);
                addn("neili", -400, me);
                me->start_busy(2);
        } else
        {
                msg += CYN "$n" CYN "眼见$N" CYN "来势汹涌，丝毫不"
                       "敢小觑，急忙闪在了一旁。\n" NOR;
                addn("neili", -200, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
