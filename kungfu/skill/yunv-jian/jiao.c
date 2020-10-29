// This program is a part of NITAN MudLIB
// he.c 双剑交错

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "双剑交错"; }

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("双剑交错只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的内功不够娴熟，不能使用双剑交错。\n");

        if ((int)me->query_skill("yunv-jian", 1) < 80)
                return notify_fail("你的玉女剑法不够娴熟，不能使用双剑交错。\n");

        if ((int)me->query_skill("quanzhen-jian", 1) < 50)
                return notify_fail("你的全真剑法不够娴熟，不能使用双剑交错。\n");

        if( query("neili", me)<400 )
                return notify_fail("你现在内力太弱，不能使用双剑交错。\n");

        if (me->query_skill_mapped("sword") != "yunv-jian")
                return notify_fail("你没有激发玉女剑法，不能使用双剑交错。\n");

        msg = HIY "$N" HIY "左手以全真剑法剑意，右手化玉女剑法剑"
              "招，双剑交错同时刺出。\n" NOR;

        ap = attack_power(me, "sword");

        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);

                damage = damage_power(me, "sword") +
                         (int)me->query_skill("quanzhen-jian", 1) +
                         (int)me->query_skill("yunv-jian", 1);

                addn("neili", -350, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "看到$N" HIR "双剑飞舞，招式中所有"
                                           "破绽都为另一剑补去，竟不知如何是好！\n"
                                           HIR"一呆之下，$N" HIR "的剑招已经破式而入！$n"
                                           HIR "一声惨叫之下，登时受了重创！\n" NOR);
        } else
        {
                me->start_busy(3);
                msg += CYN "可是$p" NOR CYN "看破了$P" NOR CYN "的企图，将"
                       "自己的全身上下护得密不透风，令$P" NOR CYN "无计可施。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
