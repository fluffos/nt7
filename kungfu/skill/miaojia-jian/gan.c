// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { HIY "流星赶月" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp, wn;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("miaojia-jian", 1) < 200)
                return notify_fail("你苗家剑法不够娴熟，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 280 )
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的内力修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<600 )
                return notify_fail("你现在真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "miaojia-jian")
                return notify_fail("你没有激发苗家剑法，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        wn = weapon->name();

        msg = HIY "$N" HIY "凝聚内力，手中" + wn + HIY "迸出万道光华，蓦然间破空"
              "声骤响，" + wn + HIY "竟离手射出，流星般向$n" HIY "奔去！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "sword");

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           HIR "$n" HIR "顿时大惊失色，只觉胸口处"
                                           "一凉，那柄" + wn + HIR "竟然已经穿胸透"
                                           "过，带出一蓬血雨！\n" NOR);
                addn("neili", -500, me);
        } else
        {
                me->start_busy(3);
                msg += HIC "$n" HIC "见" + wn + HIC "来势汹涌，心知绝"
                       "不可挡，当即向后横移数尺，终于躲闪开来。\n" NOR;
                addn("neili", -500, me);
        }

        if (userp(me) && (int)me->query_skill("miaojia-jian", 1) < 260)
        {
                msg += HIY "只见" + wn + HIY "余势不尽，又向前飞出数"
                       "丈，方才没入土中。\n" NOR;
                weapon->move(environment(me));
        } else
                msg += HIY "然而$N" HIY "身形一展，登时跃出数丈，掌"
                       "出如风，将射出的" + wn + HIY "又抄回手中。\n" NOR;

        message_combatd(msg, me, target);
        return 1;
}