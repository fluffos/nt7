// This program is a part of NITAN MudLIB
// leiting.c  排云推手「雷霆一击」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "雷霆一击"; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「雷霆一击」只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("paiyun-shou", 1) < 100)
                return notify_fail("你的排云推手不够娴熟，不会使用「雷霆一击」。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能使用「雷霆一击」！\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的内功火候不够，无法使用「雷霆一击」。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在内力不够，无法使用「雷霆一击」。\n");

        msg = HIG "$N" HIG "将真气凝于双掌，一声怒喝，双臂猛然发劲，向$n" HIG "推出。\n" NOR;

        ap = attack_power(me, "hand") +
             me->query_str()*20;

        dp = defense_power(target, "parry") +
             target->query_str()*20;

        addn("neili", -150, me);

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                damage = damage_power(me, "hand");

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "闪避不及，正中前胸，"
                                           HIR "只听“嘭”的一声，$n"
                                           HIR "狂吐一口鲜血，身子如纸鹤般向后飞出。\n" NOR);
                me->start_busy(2);
        } else
        {       msg += HIC "可是$p" HIC "早有防备，" HIC
                       "急退一步，避开了$P" HIC "这一击。\n"NOR;
                me->start_busy(2);
        }
        message_vision(msg, me, target);
        return 1;
}
