#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "万毒噬体" NOR; }

string final(object me, object target, int damage);

int perform(object me, object target)
{
        string msg;
        int damage;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的内功不够火候，难以施展" + name() + "。\n");

        if ((int)me->query_skill("wudu-shenzhang", 1) < 150)
                return notify_fail("你的五毒神掌不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "wudu-shenzhang")
                return notify_fail("你现在没有准备五毒神掌，难以施展" + name() + "。\n");

        if( query("neili", me)<120 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "将体内真气运于双掌之间，只见双掌微微泛出紫光，猛"
              "地拍向$n。\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");
        if (ap / 2 + random(ap) > dp)
        {

                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 60,
                                          (: final, me, target, damage :));

                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "眼明手快，侧身一跳$P"
                       CYN "已躲过$N这招。\n" NOR;
                me->start_busy(3);
                target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        int ap, dp;

        ap = me->query_skill("strike");
        dp = target->query_skill("force");

        target->affect_by("wudu_shenzhang",
                (["level":query("jiali", me)+random(query("jiali", me)),
                   "id":query("id", me),
                   "duration" : ap / 70 + random(ap / 30) ]));

        target->receive_wound("jing", damage / 5, me);

        return  HIR "只见$n" HIR "被$N" HIR "一掌拍中"
                "，倒退几步，却见脸色已微微泛黑。\n" NOR;

}