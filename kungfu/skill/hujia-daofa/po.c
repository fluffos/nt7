// This program is a part of NITAN MudLIB
// po.c 破字诀

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "破字诀"; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「破字诀」只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("运用「破字诀」手中必须有刀！\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 90)
                return notify_fail("你的胡家刀法不够娴熟，不会使用「破字诀」。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功修为不够高。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在内力太弱，不能使用「破字诀」。\n");

        msg = HIM "$N" HIM "手中的" + weapon->name() +
              HIM "轻轻一转，一股无形刀气悄然无息的袭向$n" HIM "。\n"NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 65,
                                           HIR "只见$n" HIR "一声惨叫，整个人如遭"
                                           "电击，口中鲜血狂喷而出！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "可是$p" HIC "默运内力，硬是抵挡了$P"
                       HIC "的这记无形刀气。\n"NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}