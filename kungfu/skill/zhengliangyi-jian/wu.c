#include <ansi.h>
#include <combat.h>

#define WU "「" HIW "无声无色" NOR "」"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( query("no_fight", environment(me)) )
                return notify_fail("在这里不能攻击他人。\n");

        // 执行天书任务的特殊房间防止龙吟中断剧情。
        if( query("skybook", environment(me)) )
                return notify_fail("在这里不能攻击他人。\n");

        if (! target || ! target->is_character()
            || query("not_living", target) )
                return notify_fail(WU "只能对对手使用。\n");

        if (target == me)
                return notify_fail("你打算攻击自己？\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，无法施展" WU "。\n");

        if ((int)me->query_skill("zhengliangyi-jian", 1) < 160)
                return notify_fail("你的正两仪剑法不够娴熟，难以施展" WU "。\n");

        if ((int)me->query_skill("dodge") < 220)
                return notify_fail("你的轻功火候不足，难以施展" WU "。\n");

        if (me->query_dex() < 45)
                return notify_fail("你现在身法太差，难以施展" WU "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在真气不够，难以施展" WU "。\n");

        if (me->query_skill_mapped("sword") != "zhengliangyi-jian") 
                return notify_fail("你没有激发正两仪剑法，难以施展" WU "。\n");

        if ((int)target->query_condition("die_guard"))
                return notify_fail("对方正被官府保护着呢，还是别去招惹。\n");

        if (target->query_competitor())
                return notify_fail("比武的时候最好是正大光明的较量。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "一声阴笑，突然使出一招「无声无色」，疾向$n"
              HIW "背后刺去。\n" NOR;

        addn("neili", -200, me);
        ap = attack_power(me,"sword");
        dp = defense_power(target,"parry");

        me->start_busy(2);
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           (: final, me, target, damage :));
        } else
        {
                msg += HIC "可是$p" HIC "看破了$P" HIC "的企图，飞身"
                       "一跃而起，将$P" HIC "这招化解于无形。\n" NOR;
        }
        message_combatd(msg, me, target);
        //me->want_kill(target);

        //if (! target->is_killing(me))
        //        target->kill_ob(me);
        return 1;
}

string final(object me, object target, int damage)
{
        object weapon;
        weapon=query_temp("weapon", me);

        return  HIW "结果$n" HIW "并没有察觉$N" HIW "的杀意，丝毫没把"
                "这一招放在心上，只\n是身子略微的向前一倾。\n" NOR +
                HIR "霎时只见$N" HIR "招数一紧，顿时只听“嗤啦”一声"
                "破空之响，$n" HIR "\n一声惨嚎，" + weapon->name() +
                HIR "剑身已透背而入。\n" NOR;
}