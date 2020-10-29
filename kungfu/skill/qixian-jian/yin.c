#include <ansi.h>
#include <combat.h>

#define YIN "「" HIM "七弦无形音" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int skill;
        int ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && !query("can_perform/qixian-wuxingjian/yin", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! me->is_fighting(target))
                return notify_fail(YIN "只能对战斗中的对手使用。\n");

        weapon=query_temp("weapon", me);

        if( weapon && query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" YIN "。\n");

        skill = me->query_skill("qixian-wuxingjian", 1);

        if (skill < 160)
                return notify_fail("你七弦无形剑修为有限，难以施展" YIN "。\n");

        if (weapon && me->query_skill_mapped("sword") != "qixian-wuxingjian")
                return notify_fail("你没有准备七弦无形剑，难以施展" YIN "。\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "qixian-wuxingjian")
                return notify_fail("你没有准备七弦无形剑，难以施展" YIN "。\n");

        if (me->query_skill("force") < 250)
                return notify_fail("你的内功修为不够，难以施展" YIN "。\n");

        if( query("neili", me)<600 )
                return notify_fail("你现在的真气不够，难以施展" YIN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        if (weapon)
        {
                msg = HIM "只见$N" HIM "一声冷哼，以内劲催动" + weapon->name()
                      + HIM "，激荡出无形琴音，铮然大响，只听“啵”的\n一声破空"
                      "之响，一束无形剑气澎湃射出，直贯$n" HIM "而去。\n" NOR;
        } else
        {
                msg = HIM "只见$N" HIM "一声冷哼，狂催内劲激荡出无形琴音，铮"
                      "然大响，只听“啵”的一声破空之\n响，一束无形剑气澎湃"
                      "射出，直贯$n" HIM "而去。\n" NOR;
        }

        ap = me->query_skill("force");
        dp = target->query_skill("force");

        if( query("max_neili", target)<10 )
        {
                msg += HIM "$N" HIM "这一招施出，可是$n"
                       HIM "竟像没事一般，丝毫无损。\n" NOR;

                me->start_busy(2);
                addn("neili", -100, me);
        } else
        // 等级相差不大的玩家不受侵害
        if( userp(target) && query("max_neili", target)+500>query("max_neili", me) )
        {
                msg += HIM "可是$n" HIM "内力深厚，轻而易举受下$N"
                       HIM "这一招，丝毫无损。\n" NOR;

                me->start_busy(2);
                addn("neili", -100, me);
        } else
        if (ap / 2 + random(ap) < dp)
        {
                msg += CYN "可是$n" CYN "急忙凝神聚气，努力使自己"
                       "不受琴音的干扰，终于化解了这一招。\n" NOR;

                me->start_busy(2);
                addn("neili", -100, me);
        } else
        {
                damage = ap + skill;
                damage += random(damage);

                target->receive_damage("jing", damage * 4 / 3, me);
                target->receive_wound("jing", damage / 3, me);

                msg += HIR "$n" HIR "只觉得$N" HIR "内力激荡，琴"
                       "音犹如一柄利剑穿透鼓膜，“哇”的喷出一口"
                       "鲜血。\n";

                me->start_busy(2);
                addn("neili", -300, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

