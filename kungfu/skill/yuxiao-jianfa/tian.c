#include <ansi.h>

#include <combat.h>

string name() { return HIC "天外清音" NOR; }

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int fmsk = me->query_skill("qimen-xuanshu", 1);
        int skill, ap, dp, neili_wound, qi_wound;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "yuxiao-jianfa")
                return notify_fail("你没有激发玉箫剑法，难以施展" + name() + "。\n");

        skill = me->query_skill("yuxiao-jianfa", 1);

        if (skill < 120)
                return notify_fail("你玉箫剑法等级不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("bibo-shengong", 1) < 120)
                return notify_fail("你碧波神功修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "一声清啸，手中" + weapon->name() +
              HIC "剑发琴音，闪动不止，剑影如夜幕般扑向$n" HIC "。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) + fmsk> dp)
        {
                addn("neili", -120, me);
                qi_wound = damage_power(me, "sword");
                qi_wound+= query("jiali", me);
                qi_wound *= 6;
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, qi_wound, 270 + fmsk/15,


                                           HIR "$n" HIR "顿时觉得眼前金光乱闪动，双耳嗡嗡"
                                           "内鸣，全身便如针扎一般！\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -50, me);
                msg += CYN "可是$n" CYN "宁心静气，随手挥洒，将$N"
                       CYN "的招数撇在一边。\n"NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}
