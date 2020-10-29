// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "玉女无情"; }

int perform(object me, object target)
{
        string msg;
        int damage, ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("玉女无情只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("unarmed", 1) < 120 )
                return notify_fail("你的基本掌法级别不够，不会使用玉女无情。\n");

        if (me->query_skill_mapped("strike") != "meiren-sanzhao")
                return notify_fail("你没有激发美人三招，难以施展「玉女无情」。\n");

        if (me->query_skill_prepared("strike") != "meiren-sanzhao")
                return notify_fail("你没有准备美人三招，难以施展「玉女无情」。\n");

        if( (int)me->query_skill("force", 1) < 120 )
                return notify_fail("你的内功还未娴熟，不能用玉女无情。\n");

        if( query("neili", me)<400 )
                return notify_fail("你现在内力太弱，不能使用玉女无情。\n");

        msg = HIB "\n\n$N真气催动，带得剑意纵横无情！\n" NOR;
        msg += HIY "\n$N右手支颐，左袖轻轻挥出，长叹一声，脸现寂寥之意，无奈中使出杀招。\n\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                addn("neili", -300, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "只听砰、砰、砰三声巨响，$n面如纸色，鲜血狂喷。\n" NOR);
                me->start_busy(2+random(2));
        }
        else
        {
                msg += HIG"$p灵光一现，纵身跃起，本能的反应帮$p逃过此劫。\n\n"NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }

        message_combatd(msg, me, target);
        return 1;
}

