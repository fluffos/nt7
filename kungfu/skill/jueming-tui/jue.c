// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "绝命一踢" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp, pp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name()+"只能空手施展。\n");

        if (me->query_skill("jueming-tui", 1) < 80)
                return notify_fail("你绝命腿法不够娴熟，难以施展"+name()+"。\n");

        if (me->query_skill_mapped("unarmed") != "jueming-tui")
                return notify_fail("你没有激发绝命腿法，难以施展"+name()+"。\n");

        if (me->query_skill_prepared("unarmed") != "jueming-tui")
                return notify_fail("你没有准备绝命腿法，难以施展"+name()+"。\n");

        if( query("neili", me)<200 )
                return notify_fail("你目前的内力不够，难以施展"+name()+"。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        switch (random(3))
        {
        case 0:
                msg = HIR "只听$N" HIR "一声冷哼，侧身飞踢，右腿横"
                      "扫向$n" HIR "，当真是力不可挡。\n" NOR;
                break;

        case 1:
                msg = HIR "$N" HIR "蓦地大喝一声，单腿猛踢而出，直"
                      "踹$n" HIR "腰际，招式极为迅猛。\n" NOR;
                break;

        default:
                msg = HIR "突然只见$N" HIR "双腿连环踢出，挟着嚯嚯"
                      "风声，以千钧之势扫向$n" HIR "。\n" NOR;
                break;
        }

        ap = attack_power(me, "unarmed") + me->query_str()*10;
        dp = defense_power(target, "dodge") + target->query_dex()*10;
        pp = defense_power(target, "parry") + target->query_str()*10;

        if (ap / 2 + random(ap) < pp)
        {
                msg += HIC "可是$n" HIC "身子一晃，硬生生架住了$N"
                       HIC "这一腿。\n" NOR;
                me->start_busy(3);
                addn("neili", -30, me);
        } else
        if (ap / 2 + random(ap) < dp)
        {
                msg += CYN "却见$n" CYN "镇定的向后一纵，闪开了$N"
                       CYN "这一腿。\n" NOR;
                me->start_busy(3);
                addn("neili", -30, me);
        } else
        {
                damage = damage_power(me, "unarmed");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "连忙格挡，却只觉得力道大"
                                           "得出奇，登时被一脚踢得飞起。\n" NOR);
                me->start_busy(2);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);
        return 1;
}
