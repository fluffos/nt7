#include <ansi.h>
#include <combat.h>

string name() { return HIW "风回雪舞" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if (me->query_skill("force") < 50)
                return notify_fail("你的内功的修为不够，难以施展" + name() + "。\n");

        if (me->query_skill("xueshan-jian", 1) < 30)
                return notify_fail("你的雪山剑法修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "xueshan-jian")
                return notify_fail("你没有激发雪山剑法，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        //msg = HIC"$N回剑旋舞，剑势不断加快，剑气呼啸四散，如片片雪花遇风，飘然而出。\n形成一个雪花形旋涡，将$n裹在内里。\n";
        msg = HIW "$N" HIW "回剑旋舞，一式「风回雪舞」施出，剑势连绵不绝，呼"
              "啸而至，欲图将$n" HIW "缠裹其中。\n" NOR;

        addn("neili", -30, me);
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "$n" HIR "只觉重重剑影铺天盖地向自己撒"
                       "来，顿被攻了个手忙脚乱，不知如何应对。\n"
                       NOR;
                target->start_busy(ap / 90 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企图，镇"
                       "定逾恒，全神应对自如。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
