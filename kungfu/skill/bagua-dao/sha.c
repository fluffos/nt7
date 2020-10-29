#include <ansi.h>
#include <combat.h>


#define SHA "「" HIR "杀龙无悔" NOR "」"

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/bagua-dao/sha", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHA "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对，难以施展" SHA "。\n");

        if (me->query_skill("force") < 250)
                return notify_fail("你的内功修为不够，难以施展" SHA "。\n");

        if (me->query_skill("bagua-dao", 1) < 180)
                return notify_fail("你的八卦刀法修为不够，难以施展" SHA "。\n");

        if (me->query_skill_mapped("blade") != "bagua-dao")
                return notify_fail("你没有激发八卦刀法，难以施展" SHA "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真气不够，难以施展" SHA "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "仰天清啸，手中" + weapon->name() +
              HIR "斜划出一道半弧，整个刀身顿时腾起凛冽无比的"
              "杀气，直贯$n" HIR "而去！\n" NOR;

        ap = attack_power(me, "blade") + me->query_str();
        dp = defense_power(target, "force") + target->query_con();

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -200, me);
                me->start_busy(3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "只听$n" HIR "一声惨叫，$N" HIR +
                                           weapon->name() + HIR "刀锋一闪，竟已嵌"
                                           "入$p" HIR "体内尺许，带出一蓬血雨。\n"
                                           NOR);
        } else
        {
                addn("neili", -100, me);
                me->start_busy(4);
                msg += CYN "$n" CYN "见$P" CYN "来势汹涌，不敢轻易抵"
                       "挡，连忙飞身腾挪，躲闪开来。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}