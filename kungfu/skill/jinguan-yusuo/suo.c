#include <ansi.h>
#include <combat.h>

string name() { return HIY "玄门金锁" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int level;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只有在战斗中才能使用。\n");

        if ((level = me->query_skill("jinguan-yusuo", 1)) < 150)
                return notify_fail("你的金关玉锁不够熟练，难以施展" + name() + "。\n" NOR);

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的内功火候不足，难以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n" NOR);

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "突然间$N" HIY "双手蓦的回圈，使出「" HIR "玄门金锁"
              HIY "」绝技，企图锁死$n" HIY "的招数。\n" NOR;

        ap = attack_power(me, "parry");
        dp = defense_power(target, "parry");

        if ( ap / 2 + random(ap) > dp )
        {
                msg += HIR "霎时$n" HIR "只觉招数一紧，双臂瘫软，全身"
                       "力道竟似被$N" HIR "牢牢锁住！\n" NOR;
                target->start_busy(ap / 90 + 2);
                addn("neili", -100, me);
                me->start_busy(1);
        } else
        {
                msg += HIC "可是$n" HIC "防守严密，丝毫不为$N"
                       HIC "的招数所乱。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}