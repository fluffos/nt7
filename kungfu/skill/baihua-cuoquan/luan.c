#include <ansi.h>
#include <combat.h>

#define LUAN "「" HIW "百花错乱" NOR "」"

inherit F_SSERVER;


int perform(object me, object target)
{
        int skill, ap, dp, damage;
        string msg;

        if( userp(me) && !query("can_perform/baihua-cuoquan/luan", me) )
                return notify_fail("你还没有受到高手指点，还不会运用" LUAN "。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(LUAN "只能对战斗中的对手使用。\n");

        skill = me->query_skill("baihua-cuoquan", 1);

        if (skill < 120)
                return notify_fail("你的百花错拳等级不够，难以施展" LUAN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，难以施展" LUAN "。\n");
 
        if (me->query_skill_mapped("unarmed") != "baihua-cuoquan")
                return notify_fail("你没有激发百花错拳，难以施展" LUAN "。\n");

        if (me->query_skill_prepared("unarmed") != "baihua-cuoquan")
                return notify_fail("你现在没有准备使用百花错拳，无法使用" LUAN "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "顿步沉身，双掌朝$n" HIW "交错打出，掌锋拳影重"
              "重叠叠，正是一招「百花错乱」。\n" NOR;
        addn("neili", -50, me);

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -150, me);
                damage = damage_power(me, "unarmed");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                           HIW "$n只感到头晕目眩，只见$N或掌、或爪、"
                                           "或拳、或指铺天盖地的向自己各个部位袭来！\n"
                                           "只一瞬间，全身竟已多了数十出伤痕，" 
                                           HIR "鲜血" HIW "狂泻不止！\n" NOR);
                me->start_busy(1);
                if (! target->is_busy())
                        target->start_busy(ap / 90 + 2);
        } else
        {
                msg += CYN "$n" CYN "只见$N" CYN "拳势汹涌，不敢轻视，急忙凝神聚"
                       "气，奋力化解开来。\n" NOR;
                addn("neili", -80, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}