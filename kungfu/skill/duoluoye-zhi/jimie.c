// This program is a part of NITAN MudLIB
// jumie.c  少林多罗叶指－菩提寂灭

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "菩提寂灭"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「菩提寂灭」只能在战斗中对对手使用。\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必须空手才能使用「菩提寂灭」！\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的内功的修为不够，不能使用这一绝技！\n");

        if (me->query_skill("duoluoye-zhi", 1) < 180)
                return notify_fail("你的多罗叶指修为不够，目前不能使用「菩提寂灭」！\n");

        if( query("neili", me)<800 || query("max_neili", me)<2500 )
                return notify_fail("你的真气不够，无法使用「菩提寂灭」！\n");

        if (me->query_skill_mapped("finger") != "duoluoye-zhi")
                return notify_fail("你没有激发多罗叶指，不能使用「菩提寂灭」！\n");

        msg = HIB "$N" HIB "运起全身功力，直扑向$n" + HIB "，双手一圈，用一股内劲" +
              "拖住$n，" + HIB "随即全力一指戳出，不惜耗费大量真元，力求一击毙敌！\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("force", 1);
        dp = defense_power(target, "dodge") + target->query_skill("force", 1);

        damage = damage_power(me, "finger");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -500, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "只见$p" HIR "一声惨号，已被$P" +
                                           HIR "一指击中，一股霸道的内力由$P" +
                                           HIR "的指尖传来，伤及经脉！\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -200, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "内力深厚，及时摆脱了"
                       CYN "$P" CYN "内力的牵扯，躲开了这一击！\n" NOR;
        }

        msg += HIR "而$P" + HIR "由于内力提升过度，经脉负荷不" +
               "了，受了不轻的内伤！\n" NOR;

        me->receive_damage("qi", damage / 10);

        message_combatd(msg, me, target);

        return 1;
}