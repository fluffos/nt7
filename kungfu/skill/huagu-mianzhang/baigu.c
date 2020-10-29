// baigu.c 白骨森然

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "白骨森然"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int damage;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("辣手化骨只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候不够，无法施展化骨掌。\n");

        if ((int)me->query_skill("huagu-mianzhang", 1) < 100)
                return notify_fail("你的化骨绵掌还不够娴熟，不会化骨掌。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真气不够，不能化骨。\n");

        if (me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("你没有激发化骨绵掌，无法施展化骨掌。\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        addn("neili", -100, me);

        msg = BLU "$N"BLU"面无表情，蓦然游身而上，绕着$n"BLU"疾转数圈，猛地身形一缩，转到$n"BLU"身前，\n"
              "右手划出一道光圈，往$n"BLU"丹田印了下去！\n"NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if( ap / 2 + random(ap) > dp )
        {
                me->start_busy(2);
                if( !target->is_busy() )
                        target->start_busy(random(3));
                damage=query("neili", target)/2;
                if (damage < 300) damage = 300;

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                          CYN"$n"CYN"匆忙闪身，却已不及，只觉浑身真气难聚，人如软泥般向后瘫倒！\n"NOR);
        } else
        {
                me->start_busy(2);
                msg += HIY"可是$p也随着纵身斜跃，避开了丹田要害。\n"NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
