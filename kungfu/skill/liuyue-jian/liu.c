// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "流月剑诀" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if (me->query_skill("force") < 180)
                return notify_fail("你的内功的修为不够，难以施展" + name() + "。\n");

        if (me->query_skill("liuyue-jian", 1) < 120)
                return notify_fail("你的流月剑舞修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "liuyue-jian")
                return notify_fail("你没有激发流月剑舞，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "一声清啸，剑法忽变，手中" + weapon->name() + HIY
              "轻轻划出，带出一条无比绚丽的剑芒，遥指$n" HIY "而去。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -150, me);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "顿时目瞪口呆，一个不慎，被$N"
                                           HIR "精妙的剑招刺中，鲜血飞溅！\n" NOR);
                me->start_busy(2);
        } else
        {
                addn("neili", -60, me);

                msg += CYN "可是$p" CYN "并不慌乱，收敛心神，轻轻格挡开了$P"
                       CYN "的剑招。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}