#include <ansi.h>
#include <combat.h>

string name() { return HIG "啸沧海" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;
        int fmsk;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("tanzhi-shentong", 1) < 200)
                return notify_fail("你的弹指神通不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("你没有激发弹指神通，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("你没有准备弹指神通，难以施展" + name() + "。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIG "突然间$N" HIG "指锋一转，力聚指尖“嗤”的弹出一道紫芒，直袭$n"
              HIG "气海大穴。\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "force");
        fmsk = me->query_skill("qimen-xuanshu", 1); 

        damage = damage_power(me, "finger");
        damage+= query("jiali", me);

        addn("neili", -500, me);
        if (ap / 2 + random(ap) + fmsk > dp) 
        {
                target->receive_damage("jing", damage*4/3 + fmsk / 2, me); 
                target->receive_wound("jing", damage / 3 + fmsk / 3, me); 
                addn("neili", -damage*3-fmsk, target);

                if( query("neili", target)<0 )
                        set("neili", 0, target);

                msg += HIR "$n" HIR "只觉$N" HIR "指风袭体，随即上体一"
                       "阵冰凉，顿感真气涣散几欲晕厥。\n" NOR;
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "防守严密，紧守门户，顿时令$P"
                       CYN "的攻势化为乌有。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
