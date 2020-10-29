#include <ansi.h>
#include <combat.h>

#define HUAN "「" HIM "云霞幻生" NOR "」"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon, weapon2;
        int skill, ap, dp, damage;
        string wn, msg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUAN "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不对，难以施展" HUAN "。\n");

        skill = me->query_skill("caiyan-gong", 1);

        if (skill < 120)
                return notify_fail("你采燕功等级不够，难以施展" HUAN "。\n");

        if (me->query_skill("dodge") < 180)
                return notify_fail("你的轻功火候不够，难以施展" HUAN "。\n");
 
        if (me->query_skill_mapped("club") != "caiyan-gong")
                return notify_fail("你没有激发采燕功，难以施展" HUAN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在的真气不够，难以施展" HUAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        wn = weapon->name();

        message_sort(HIM "\n$N" HIM "蓦地施出「" HIW "云霞幻生"
                     HIM "」绝技，手中" + wn + HIM "由一变二，"
                     "由二变四，由四变八，由八变十六……竟幻出"
                     "无数根" + wn + HIM "。棍影层层叠叠朝四周"
                     "疾刺而出，企图封锁$n" HIM "的退路。\n" NOR,
                     me, target);

        ap = attack_power(me, "club");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -80, me);
                damage = damage_power(me, "club");
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           (: final, me, target, damage :));

                me->start_busy(2);
        } else
        {
                msg = CYN "$n" CYN "大惊之下急忙跃开数步，方才摆脱$N"
                      CYN "棍影的范围。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_vision(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        string msg;

        msg = HIR "$p大惊失色之下接连被$P击中数棍"
              "，当即疼痛难当，";

        if (random(3) >= 1 && ! target->is_busy())
        {
                target->start_busy(damage /60+ 2);
                msg += "无暇反击。\n" NOR;
        } else
                msg += "急声长呼。\n" NOR;

        return  msg;
}