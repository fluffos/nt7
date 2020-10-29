// This program is a part of NITAN MudLIB
// fei.c 魂魄飞扬

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "魂魄飞扬" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("qishang-quan", 1) < 160)
                return notify_fail("你的七伤拳不够娴熟，无法施展" + name() + "。\n");

        if ((int)me->query_skill("force", 1) < 160)
                return notify_fail("你的内功修为还不够，无法施展" + name() + "\n");

        if (query("max_neili", me) < 2200)
                return notify_fail("你内力修为不足，无法施展" + name() + "\n");

        if ((int)query("neili", me) < 350)
                return notify_fail("你现在真气不够，无法施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "qishang-quan")
                return notify_fail("你没有准备使用七伤拳，无法施展" + name() + "。\n");

        if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "\n$N" HIY "深吸一口起，将真气运于双拳之上，施出绝招「" HIR "魂魄飞扬" HIY
              "」，右拳平平一拳直出，\n但见普通一拳之中蕴涵了无穷的力量，拳未到风先至，猛然"
              "间袭向$n" HIY "。\n" NOR;

        ap = attack_power(me, "cuff") +
             me->query_skill("force");

        dp = defense_power(target, "parry") +
             target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "cuff");
                damage+= query("jiali", me);

                addn("neili", -320, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
                                           HIR "只听“砰”地一声，$N" HIR "一拳正好打中$n" HIR "胸"
                                           "口，$n" HIR "怪叫一声，吐出一口淤血！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "可是$p" HIC "奋力招架，硬生生的挡开了$P"
                       HIC "这一招。\n"NOR;
                addn("neili", -180, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
