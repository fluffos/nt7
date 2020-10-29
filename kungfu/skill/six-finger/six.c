// This program is a part of NITAN MudLIB
// six.c 六脉剑气

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "六脉剑气" NOR; }

int perform(object me, object target)
{
        mapping prepare;
        string msg;
        int skill;
        int delta;
        int i, ap, dp;
        int n;
        int fmsk = me->query_skill("qimai-liuzhuan", 1);

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("你没有准备使用六脉神剑，无法施展" + name() + "。\n");

        skill = me->query_skill("six-finger", 1);

        if (skill < 220)
                return notify_fail("你的六脉神剑修为有限，无法使用" + name() + "！\n");

        if (me->query_skill("force") < 400)
                return notify_fail("你的内功火候不够，难以施展" + name() + "！\n");

        if( query("max_neili", me)<7000 )
                return notify_fail("你的内力修为没有达到那个境界，无法运转内"
                                   "力形成" + name() + "！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真气不够，现在无法施展" + name() + "！\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必须是空手才能施展" + name() + "！\n");

        if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "摊开双手，手指连弹，霎时间空气炙热，几"
              "欲沸腾，六道剑气分自六穴，一起杀向$n" HIY "！\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        ap *= 3;
        if (ap / 2 + random(ap) > dp)
        {
                delta = skill / 2;
                if( (n = fmsk / 100) >= 1 )
                {
                        msg += HIM"$N"HIM"运用气脉流转的辅助，使得六脉剑气伤害更强。\n"NOR;
                        delta += delta * n * 10;
                }
                msg += HIR "$n" HIR "见此剑气纵横，微一愣神，不禁心萌退意。\n" NOR;
                target->set_weak(5);
        } else
                delta = 0;

        message_combatd(msg, me, target);

        addn("neili", -300, me);
        addn_temp("apply/attack", delta, me);
        addn_temp("apply/defense", delta, me);
        addn_temp("apply/unarmed_damage", delta*5, me);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                set_temp("six-finger/hit_msg", i, me);
                COMBAT_D->do_attack(me, target, 0, TYPE_LINK);
        }
        addn_temp("apply/attack", -delta, me);
        addn_temp("apply/defense", -delta, me);
        addn_temp("apply/unarmed_damage", -delta*5, me);
        delete_temp("six-finger/hit_msg", me);
        me->start_busy(1 + random(3));

        return 1;
}
