// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "缠丝擒拿" NOR; }

string final(object me, object target, int damage);

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name()+"只能空手施展。\n");

        skill = me->query_skill("chansi-shou", 1);

        if (skill < 120)
                return notify_fail("你缠丝擒拿手等级不够，难以施展"+name()+"。\n");

        if (me->query_skill_mapped("hand") != "chansi-shou")
                return notify_fail("你没有激发缠丝擒拿手，难以施展"+name()+"。\n");

        if (me->query_skill_prepared("hand") != "chansi-shou")
                return notify_fail("你没有准备缠丝擒拿手，难以施展"+name()+"。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在的真气不够，难以施展"+name()+"。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "悄然贴近$n" HIW "，施出缠丝擒拿，双手忽"
              "折忽扭，或抓或甩，直琐$p" HIW "各处要脉。\n" NOR;

        ap = attack_power(me, "hand");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -80, me);
                damage = damage_power(me, "hand");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           (: final, me, target, damage :));
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$n" CYN "的看破了$N"
                       CYN "的招式，巧妙的招架拆解，没露半点破绽。\n" NOR;
                addn("neili", -20, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        string msg;

        msg = HIR "却见$n" HIR "奋力抵抗，可终究无法"
              "摆脱$N" HIR "的攻势，连中数掌，";

        if (random(3) >= 1 && ! target->is_busy())
        {
                target->start_busy(damage / 120+2);
                msg += "难以反击。\n" NOR;
        } else
                msg += "鲜血狂喷。\n" NOR;

        return  msg;
}