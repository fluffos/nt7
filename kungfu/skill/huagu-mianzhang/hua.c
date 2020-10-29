// This program is a part of NITAN MudLIB
// hua.c 化骨绵掌

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "化骨"; }

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int damage;
        int ap, dp;
        int fmsk = me->query_skill("shenlong-dafa", 1);

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

        msg = MAG "$N" MAG "掌出如风，轻轻拍向$n" MAG "的肩头。\n"NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        ap *= 2;
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "strike");
                damage+= query("jiali", me);
                damage *= 6;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 300+fmsk/15,
                                          (: final, me, target, damage :));
        } else
        {
                msg += CYN "可是$p" CYN "急忙闪在一旁，躲了开去。\n" NOR;
                me->start_busy(3);
        }

        message_combatd(msg, me, target);
        return 1;
}

string final(object me, object target, int damage)
{
        int lvl = me->query_skill("huagu-mianzhang", 1) / 2 * 3;

        target->affect_by("huagu",
                (["level":query("jiali", me)+random(query("jiali", me)),
                   "id":query("id", me),
                   "duration" : lvl / 60 + random(lvl / 60) ]));

        return HIR "结果只听扑的一声，$p被$P一掌拍中，只"
               "觉得全身暖洋洋的，感到有点轻飘无力。\n" NOR;
}
