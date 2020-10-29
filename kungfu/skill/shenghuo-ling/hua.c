// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "光华令" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, skill, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        skill = me->query_skill("shenghuo-ling",1);

        if (! (me->is_fighting()))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "sword")
                return notify_fail("你使用的兵器不对，不能使用圣火令法之" + name() + "。\n");

        if (skill < 140)
                return notify_fail("你的圣火令法等级不够, 不能使用圣火令法之" + name() + "。\n");

        if (query("max_neili", me) < 1500)
                return notify_fail("你的内力修为不足，不能使用圣火令法之" + name() + "。\n");

        if (query("neili", me) < 340)
                return notify_fail("你的内力不够，不能使用圣火令法之" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "猛吸一口气，使出圣火令法之「" HIW "光华令" HIY "」，手中"
              + weapon->name() + NOR + HIY "御驾如飞，幻出无数道金"
              "芒，将$n" HIY "笼罩起来！\n" NOR;

        ap = attack_power(me, "sword") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                damage *= 4;

                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                       HIR "$n" HIR "只觉万道金芒铺天盖地席卷而来，"
                       "完全无法阻挡。顿时只感全身几处刺痛，鲜血飞"
                       "溅而出！\n" NOR);

                me->start_busy(2);
        } else
        {
                msg += CYN "可是$n" CYN "看准$N" CYN "的破绽，猛地向"
                       "前一跃，跳出了$N" CYN "的攻击范围。\n"NOR;
                addn("neili", -150, me);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        return 1;
}
