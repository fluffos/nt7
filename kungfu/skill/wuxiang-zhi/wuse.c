// This program is a part of NITAN MudLIB
// wuse.c  无色无相

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "无色无相"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「无色无相」只能在战斗中对对手使用。\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必须空手才能使用「无色无相」！\n");

        if (me->query_skill("force") < 100)
                return notify_fail("你的内功的修为不够，不能使用这一绝技！\n");

        if (me->query_skill("wuxiang-zhi", 1) < 150)
                return notify_fail("你的无相指修为不够，目前不能使用「无色无相」！\n");

        if( query("neili", me)<400 )
                return notify_fail("你的真气不够，无法使用「无色无相」！\n");

        if (me->query_skill_mapped("finger") != "wuxiang-zhi")
                return notify_fail("你没有激发大力无相指，不能使用「无色无相」！\n");

        msg = HIY "$N" HIY "聚起全身功力，汇聚于右指，纵身而上，"
              HIY "向$n扑去，同时一指划出，如同流星一般击向$n" + HIY "！\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                addn("neili", -200, me);

                msg += HIR "只见$p" HIR "一声惨叫，已被点中胸口要穴，"
                       "$p" HIR "只觉得胸口气血汹涌，全身气血"
                       "倒流，哇的一声吐出一口鲜血，苦不堪言！\n" NOR;
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 70);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$N" CYN "的企图，轻轻"
                       CYN "向后飘出数丈，躲过了这一致命的一击！\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}