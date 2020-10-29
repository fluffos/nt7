#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "大海捞针" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = query_temp("weapon", me))
           || (string)query("skill_type", weapon) != "staff")
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 140)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if ((int)query("neili", me) < 200)
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("yinhu-zhang", 1) < 100)
                return notify_fail("你银瑚杖法火候不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("staff") != "yinhu-zhang")
                return notify_fail("你没有激发银瑚杖法，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIM "\n$N" HIM "一声暴喝，猛然间腾空而起，施出绝招「" HIW "大海捞"
              "针" HIM "」，手中" + weapon->name() + HIM "从天而降，气势惊人地"
              "袭向$n" HIM "。\n" NOR;

        message_sort(msg, me, target);

        ap = attack_power(me, "staff");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "staff");

                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 75,
                                           HIR "$n" HIR "完全无法看清招中虚实，只"
                                           "听「嘭」地一声，已被$N" HIR "击中肩膀。\n" NOR);
                me->start_busy(3);
                addn("neili", -180, me);
        } else
        {
                msg = CYN "可是$n" CYN "奋力招架，左闪右避，好不容"
                       "易抵挡住了$N" CYN "的攻击。\n" NOR;
                me->start_busy(4);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);

        return 1;
}