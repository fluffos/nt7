// 圣火焚躯

#include <ansi.h>

inherit F_SSERVER;

string name() { return "圣火焚躯"; }

int perform(object me, object target)
{
        int damage;
        int ap,dp;
        string msg,str;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("你只能对战斗中的对手施展圣火焚躯。\n");

        if (query_temp("weapon", me))
                return notify_fail("你只有空手才能使用圣火拳。\n");

        if (!(me->query_skill_mapped("cuff") == "shenghuo-quan"))
                return notify_fail("你并没有激发圣火拳，如何用圣火焚躯？\n");

        if (!(me->query_skill_prepared("cuff") == "shenghuo-quan"))
                return notify_fail("你并没有准备圣火拳，如何用圣火焚躯？\n");

        if ((int)me->query_skill("shenghuo-quan", 1) < 60)
                return notify_fail("你的圣火拳火候不够。\n");

        if ((int)query("max_neili", me) < 200)
                return notify_fail("你的内力修为不足，无法用内力施展圣火焚躯。\n");

        if ((int)query("neili", me) < 100)
                return notify_fail("你现在内息不足，无法用内力施展圣火焚躯。\n");

        msg = HIR "只见$N" HIR "一声呼啸，面脸突显一片红光，双拳收于胸口，顷刻从肩膀到拳头都成为赤色。\n\n"
              "$N" HIR "深吸一口气，双拳闪电般飞出，滚滚热浪冲$n" HIR "飞卷而去，令人感到一阵窒息。\n\n"NOR;

        me->start_busy(1 + random(2));
        addn("neili", -50, me);

        damage = damage_power(me, "cuff");

        ap = attack_power(me, "cuff") + me->query_str()*10;
        dp = defense_power(target, "dodge") + target->query_dex()*10;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIR "$n" HIR "见炙热拳风扑面涌来，只觉浑身一阵剧痛，"
                               "已被卷入猛烈的拳劲，烈火席卷全身，不由闷哼一声。\n\n" NOR;
                        target->receive_damage("qi", damage, me );
                        target->receive_wound("qi", random(damage/2), me);
                        target->start_busy(2);
                        str = COMBAT_D->status_msg((int)query("qi", target) * 100 /(int)query("max_qi", target));
                        msg += "($n"+str+")\n";
        } else
        {
                msg += HIY "$n" HIY "见状连忙提运内力，双足点地"
                       "，身形急退，避开了$N" HIY "扑面而来的炙热拳风。\n\n";
        }

        message_combatd(msg, me, target);
        //me->want_kill(target);
        //if (! target->is_killing(me)) target->kill_ob(me);
        return 1;
}