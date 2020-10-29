// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIM "宁氏一剑" NOR; }

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

        if (me->query_skill("dodge", 1) < 100)
                return notify_fail("你的基本轻功的修为不够，难以施展" + name() + "。\n");

        if (me->query_skill("force", 1) < 100)
                return notify_fail("你的基本内功的修为不够，难以施展" + name() + "。\n");

        if (me->query_skill("yunv-sword", 1) < 100)
                return notify_fail("你的淑女剑法修为不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "yunv-sword")
                return notify_fail("你没有激发淑女剑法，难以施展" + name() + "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你现在真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "\n$N" HIW "娇喝一声，飞身而起，使出绝招「" HIM "宁氏一剑" HIW "」将毕生功力运于\n"
              + weapon->name() + HIW "上，顿时剑光四射，剑势如虹，将$n" HIW "笼罩" HIW "。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -220, me);
                me->start_busy(1 + random(3));
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "开料不及，正欲躲闪，却已经中剑。\n" NOR);
        } else
        {
                addn("neili", -120, me);
                me->start_busy(2);
                msg += CYN "可是$n" CYN "随手招架，竟将这招化解。\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}