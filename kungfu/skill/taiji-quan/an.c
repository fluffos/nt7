// an.c 太极拳「按」字诀

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "按字诀"; }

int perform(object me, object target)
{
        int damage, acter, ap, dp, taoism;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「按字诀」只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能使用「按字诀」！\n");

        if ((int)me->query_skill("taiji-quan", 1) < 200)
                return notify_fail("你对太极拳理的理解还不够，不会使用「按字诀」。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在真气太弱，不能使用「按字诀」。\n");

        msg = HIG "$N" HIG "双拳上下挥动，使出太极拳「按字诀」，$n"
              HIG "感到一股强大的劲力从头顶压落。\n" NOR;

        addn("neili", -200, me);

        dp = (defense_power(target, "parry") + target->query_skill("force", 1)) / 3;

        if( query("character", me) == "光明磊落" ||
            query("character", me) == "国土无双" ||
            query("character", me) == "狡黠多变" )
               acter = 3;
        else
               acter = 4;

        taoism = me->query_skill("taoism", 1);

        ap = (attack_power(me, "cuff") + me->query_skill("taiji-shengong", 1) +
              taoism) / acter;

        if (target->is_bad())   ap += ap / 2;

        if (ap / 2 + random(ap) > dp / 2 || !living(target))
        {
                me->start_busy(2);
                if( !target->is_busy() )
                        target->start_busy(1+random(3));

                damage = damage_power(me, "cuff");

                if( query("shen", me)/800<5000 )
                     damage += 5000;
                else
                     damage+=query("shen", me)/800;

                damage+=query("jiali", me)*2;

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                           damage, 70,
                                           HIY "$n" HIY "登感呼吸不畅，胸闷难当，"
                                           HIY "喉头一甜，狂喷数口"HIR"鲜血"HIY"！\n"
                                           ":内伤@?");
        } else
        {
                me->start_busy(3);
                msg += HIY "$p" HIY "急运内功，聚劲于外，挺身硬接了$P"
                       HIY "这一招，“砰”的一声巨响，双方各自震退数步！\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
