// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIC "驾字诀" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, weapon2;
        int skill, ap, dp, damage;
        string wn1, wn2, msg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        skill = me->query_skill("taiji-jian", 1);

        if (skill < 150)
                return notify_fail("你的太极剑法等级不够，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "taiji-jian")
                return notify_fail("你没有激发太极剑法，难以施展" + name() + "。\n");

        if( !objectp(weapon2=query_temp("weapon", target)) )
                return notify_fail("对方没有使用兵器，难以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        wn1 = weapon->name();
        wn2 = weapon2->name();

        msg = HIC "只见$N" HIC "收摄心神，以剑意运剑，手中" + wn1 + HIC "每剑均以弧形"
              "刺出，弧形收回，每发一招都似放\n出一条细丝，要去缠在$n" HIC "的" + wn2 +
              HIC "之上。\n" NOR;
        addn("neili", -50, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap * 4 / 3) > dp)
        {
                addn("neili", -30, me);
                damage = damage_power(me, "sword");

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "却见$n" HIR "手中" + wn2 + HIR "被" +
                                           wn1 + HIR "缠住后不断增加重量，招数顿见涩"
                                           "滞，真力不由狂泻而出。\n" NOR);

                if (ap / 2 + random(ap) > dp && ! target->is_busy())
                        target->start_busy(ap / 80 + 2);
                me->start_busy(2);
        } else
        {
                msg += CYN "$n" CYN "不禁大惊失色，急忙跃开数步，方才摆脱$N"
                       CYN "的力道。\n" NOR;
                addn("neili", -10, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
