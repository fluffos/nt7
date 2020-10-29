// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "混沌一阳" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;

        /*
        if (!SKILLS_D->valid_perform(me, __FILE__))
                return 0;
        */
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail(name() + "只能空手施展。\n");

        if (me->query_skill("jiuyang-shengong", 1) < 180)
                return notify_fail("你的九阳神功还不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "jiuyang-shengong")
                return notify_fail("你现在没有激发九阳神功为拳脚，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("你现在没有激发九阳神功为内功，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "jiuyang-shengong")
                return notify_fail("你现在没有准备使用九阳神功，难以施展" + name() + "。\n");

        if (query("neili", me) < 300)
                return notify_fail("你的内力不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "跨前一步，双手回圈，颇得太极之意。掌心顿时闪"
              "出一个气团，向$n" HIR "电射而去。\n" NOR;

        ap = attack_power(me, "force") + me->query_con()*10;
        dp = defense_power(target, "force") + target->query_con()*10;

        addn("neili", -50, me);

        if (ap / 2 + random(ap) < dp)
        {
                msg += HIY "然而$n" HIY "全力抵挡，终于将$N" HIY
                       "发出的气团拨开。\n" NOR;
                me->start_busy(3);
        } else
        {
                addn("neili", -200, me);
                me->start_busy(1);
                damage = damage_power(me, "force");
                damage+= query("jiali", me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 150,
                                           HIR "$n" HIR "急忙抽身后退，可是气团射"
                                           "得更快，只听$p" HIR "一声惨叫，鲜血飞"
                                           "溅！\n" NOR);
        }
        message_combatd(msg, me, target);
        return 1;
}
