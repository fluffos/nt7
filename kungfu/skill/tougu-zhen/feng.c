#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "封杀" NOR; }

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

        if ((int)me->query_skill("tougu-zhen", 1) < 100)
                return notify_fail("你的透骨针还不够娴熟，无法施展" + name() + "！\n");

        if ((int)me->query_skill("force") < 260)
                return notify_fail("你内功火候不够，难以施展" + name() + "！\n");

        if ((int)query("max_neili", me) < 2400)
                return notify_fail("你的真气不够，无法施展" + name() + "！\n");

        if ((int)query("neili", me) < 350)
                return notify_fail("你的真气不够，无法施展" + name() + "！\n");

        if (me->query_skill_prepared("finger") != "tougu-zhen")
                return notify_fail("你没有准备使用透骨针，无法使用" + name() + "！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "使出透骨针「" HIR "封 杀" HIW "」绝技，手指挥舞，幻出漫天寒星"
              "，携带着阴寒之劲直封$n" HIW "各处要穴！\n" NOR;

        lvl = me->query_skill("tougu-zhen", 1);

        ap = attack_power(me, "finger") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                           (: final, me, target, lvl :));

                addn("neili", -280, me);
                me->start_busy(1);
        } else
        {
                msg += CYN "可是$n急忙退闪，连消带打躲开了这一击。\n" NOR;
                me->start_busy(3);
                addn("neili", -50, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int lvl)
{
       target->affect_by("tougu_zhen",
                        ([ "level"    : query("jiali", me) + random(query("jiali", me)),
                           "id"       : query("id", me),
                           "duration" : lvl / 50 + random(lvl / 20) ]));

        return HIR "结果只听$n一声惨嚎，被攻个正着，透骨针极寒之劲攻心，全身瘫麻，鲜血狂喷！\n" NOR;
}