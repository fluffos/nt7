// This program is a part of NITAN MudLIB
// foxin.c 佛心剑

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "佛心剑"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「佛心剑」只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的内功的修为不够，不能使用这一绝技！\n");

        if (me->query_skill("fumo-jian", 1) < 135)
                return notify_fail("你的伏魔剑法修为不够，目前不能使用佛心剑！\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真气不够，不能使用佛心剑！\n");

        if (me->query_skill_mapped("sword") != "fumo-jian")
                return notify_fail("你没有激发伏摩剑，不能使用佛心剑！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "手中" + weapon->name() +
              HIC "缓缓伸出，封住了$n" + HIC "的退路，随"
              "即一抖，化出数个剑花逼向$p" HIC "。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -150, me);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "结果$p" HIR "一个不慎，被$P" HIR
                                           "一剑划过气门，内息就如翻江倒海一"
                                           "般，身子摇摇欲坠！\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "并不慌乱，沉稳的将$P"
                       CYN "的招一一化解。\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}
