// This program is a part of NITAN MudLIB
// wuji.c 横行无忌

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "横行无忌"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「横行无忌」只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("运用「横行无忌」必须手中持杖！\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的内功火候不够，难以运用使用「横行无忌」！\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不够，无法使用「横行无忌」！\n");

        if ((int)me->query_skill("lingshe-zhangfa", 1) < 150)
                return notify_fail("你的灵蛇杖法还不到家，无法使用「横行无忌」！\n");

        if (me->query_skill_mapped("staff") != "lingshe-zhangfa")
                return notify_fail("你没有激发灵蛇杖法，无法使用「横行无忌」！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "一声冷笑，手中的" + weapon->name() + HIY "忽然变得"
              "如同活物一般，时上时下，忽左忽右，不知攻向$n" HIY "何处！\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "staff");
                addn("neili", -200, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "实在无法捕做到$P"
                                           HIR "的实招，接连挡空，连中数招，"
                                           "登时吐了一口鲜血！\n" NOR);
                me->start_busy(2);
                if (! target->is_busy())
                target->start_busy(1);
        } else
        {
                msg += CYN "$n" CYN "奋力招架，总算抵挡住了$P"
                       CYN "的攻击！\n" NOR;
                addn("neili", -80, me);
                me->start_busy(3);
                if (! target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}
