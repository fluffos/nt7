// This program is a part of NITAN MudLIB
// xiyan.c

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIM "吸焰令" NOR; }

int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword")
                return notify_fail("你使用的兵器不对，不能使用圣火令法之" + name() + "。\n");

        skill = me->query_skill("shenghuo-ling", 1);

        if (! objectp(weapon2 = query_temp("weapon", target)))
                return notify_fail("对方没有使用兵器，不能使用圣火令法之" + name() + "。\n");

        if (skill < 140)
                return notify_fail("你的圣火令法等级不够, 不能使用圣火令法之" + name() + "。\n");

        if (query("max_neili", me) < 1500)
                return notify_fail("你的内力修为不足，不能使用圣火令法之" + name() + "。\n");

        if (query("neili", me) < 300)
                return notify_fail("你的真气不够，不能使用圣火令法之" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIM "突然$N" HIM "诡异的一笑，使出圣火令法之吸焰"
              "令，手中" + weapon->name() + HIM "幻出数个小圈"
              "，将$n" HIM "的" + weapon2->name() + HIM "紧紧"
              "缠住。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -240, me);
                msg += HIM "$n" HIM "只见眼前无数寒光颤跃闪动，顿时只感"
                      "头晕目眩，手腕一麻，手中" + weapon2->name() + HIM
                      "已被$N" HIM "纳入怀中！\n" NOR;
                me->start_busy(2);
                weapon2->move(me, 1);
        } else
        {
                addn("neili", -100, me);
                msg += CYN "可是$n" CYN "看破$N" CYN "的企图，将手中兵"
                      "刃挥舞得密不透风，使得$N" CYN "无从下手。\n" NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        return 1;
}
