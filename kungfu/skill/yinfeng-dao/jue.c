#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "绝杀" NOR; }

string final(object me, object targer, int lvl);

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;
        int lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中使用。\n");

        if ((int)me->query_skill("yinfeng-dao", 1) < 140)
                return notify_fail("你的阴风刀还不够娴熟，无法施展" + name() + "绝技！\n");

        if ((int)me->query_skill("force") < 260)
                return notify_fail("你内功火候不够，难以施展" + name() + "绝技！\n");

        if ((int)query("max_neili", me) < 2400)
                return notify_fail("你的真气不够，无法施展" + name() + "绝技！！\n");

        if ((int)query("neili", me) < 400)
                return notify_fail("你的真气不够，无法施展" + name() + "绝技！！\n");

        if (me->query_skill_mapped("strike") != "yinfeng-dao")
                return notify_fail("你没有激发阴风刀，无法使用" + name() + "绝技！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "使出阴风刀「" HIR "绝 杀" HIW"」绝技，掌劲幻出一片片切骨寒"
              "气如飓风般裹向$n全身！\n" NOR;

        lvl = me->query_skill("yinfeng-dao", 1);

        ap = attack_power(me, "strike") + me->query_skill("force");
        dp = defense_power(target, "parry") + me->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                           (: final, me, target, lvl :));

                addn("neili", -350, me);
                me->start_busy(1);
        } else
        {
                msg += CYN "可是$n急忙退闪，连消带打躲开了这一击。\n" NOR;
                me->start_busy(3);
                addn("neili", -150, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int lvl)
{
       target->affect_by("yinfeng_dao",
                       ([ "level"    : query("jiali", me) + random(query("jiali", me)),
                          "id"       : query("id", me),
                          "duration" : lvl / 50 + random(lvl / 20) ]));

       return HIR "结果只听$n一声惨嚎，全身几处要穴同时被阴风寒劲砍中，疼若刮骨，鲜血狂泄而出！\n" NOR;
}
