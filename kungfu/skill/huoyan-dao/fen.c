// This program is a part of NITAN MudLIB
// fen.c 焚身

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "焚身"; }
int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「焚身」只能对战斗中的对手使用。\n");

        skill = me->query_skill("huoyan-dao", 1);

        if (skill < 120)
                return notify_fail("你的火焰刀等级不够，还不能使出「焚身」！\n");

        if (me->query_skill("force") < 120)
                return notify_fail("你的内功火候不够，不能使用这样绝技。\n");

        if( query("neili", me)<400 )
                return notify_fail("你的内力不够，无法运功！\n");

        if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "聚气于掌，使出一招「焚身」，无形刀气向$n"
              HIR "的胸口击去。\n"NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -300, me);
                damage = damage_power(me, "force");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50,
                                           HIR "$p" HIR "强运内力试图抵抗，然而无法掌握$P"
                                           HIR "内力的变化，结果被$P"
                                           HIR "的无形刀气重创在胸口！\n" NOR);
                me->start_busy(2);

        } else
        {
                msg += HIC "却见$p" HIC "不慌不忙，轻轻一闪，躲过了$P"
                       HIC "的必杀一击！\n" NOR;
                addn("neili", -150, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
