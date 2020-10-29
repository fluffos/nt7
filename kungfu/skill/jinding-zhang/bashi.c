// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "八式合一" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int count,d_count,qi, maxqi, skill;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的内力还不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功的修为不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("jinding-zhang", 1) < 100)
                return notify_fail("你的金顶绵掌的修习不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "jinding-zhang")
                return notify_fail("你没有激发金顶绵掌，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "jinding-zhang")
                return notify_fail("你现在没有准备使用金顶绵掌，难以施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "深深吸了一口气，提起全身的功力于"
              "双掌猛力拍出，只听得骨骼一阵爆响！\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage += (damage * (int)me->query_skill("linji-zhuang", 1)/100)/100;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "只见漫天掌影飘忽不定的罩向$n" HIR
                                           "全身各个部位，$n" HIR "顿时接连中了数"
                                           "掌！\n" NOR);
                addn("neili", -100, me);
                me->start_busy(2);
         } else
         {
                msg += CYN "可是$p" CYN "猛地向后一跃，跳出了$P"
                       CYN "的攻击范围。\n" NOR;
                me->start_busy(3);
         }
         message_combatd(msg, me, target);
         return 1;
}
