// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "震字诀"; }

int perform(object me, object target)
{
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! target->is_character() ||
            ! me->is_fighting(target))
                return notify_fail("震字决只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("wudang-zhang", 1) < 100)
                return notify_fail("你的武当棉掌不够娴熟，不会使用震字诀。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够！\n");

        msg = HIB "$N气运丹田，使出棉掌震字决，双掌泛起凌厉掌风，拍向$n。\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                addn("neili", -400, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                        HIR "$n 茫然不知所措，结果被$N一掌击中前胸，$n眼前一黑，被击飞出两丈许！！！\n" NOR);
                me->start_busy(2);
        } else
        {
                addn("neili", 200, me);
                me->start_busy(2);
                msg += HIG "可是$p看破了$P的企图，早就闪在了一边。\n" NOR;
        }

        message_combatd(msg, me, target);
        return 1;
}

