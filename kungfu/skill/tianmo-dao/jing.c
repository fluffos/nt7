// jing.c 惊天一击

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "惊天一击"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「惊天一击」只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对。\n");

        ap = attack_power(me, "blade");

        if (ap < 120)
                return notify_fail("你的天魔刀法等级不够, 不能使用「惊天一击」！\n");

        if( query("neili", me)<120 )
                return notify_fail("你的真气不够，无法运用「惊天一击」！\n");

        msg = HIY "$N" HIY "一声冷哼，跨步前移，手中" + weapon->name() +
              HIY "呤呤作响，如闪电般砍向$n" HIY "。\n" NOR;

        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                addn("neili", -80, me);
                damage = damage_power(me, "blade");

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "看清来招，飞身闪躲，然而$N"
                                           HIR "忽而招式一变，手中" + weapon->name() +
                                           HIR "斜上挥向$n" HIR "的双腿。\n"
                                           HIR "只听$n" HIR "连声惨呼，已被砍中，点点血"
                                           HIR "滴如雨点般漫天洒下。\n" NOR);
                me->start_busy(1 + random(3));
        } else
        {
                addn("neili", -30, me);
                msg += HIC "可是$n" HIC "早已看清$N"
                       HIC "的企图，轻巧地将$P" HIC "的来招架开。\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
