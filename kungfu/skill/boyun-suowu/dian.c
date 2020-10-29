#include <ansi.h>

inherit F_SSERVER;

string name() { return "云雾暗点"; }

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( query_temp("weapon", me) )
                return notify_fail("你手上不能装备任何东西。\n");

        if (! me->is_fighting(target))
                return notify_fail("只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("boyun-suowu", 1) < 100 )
                return notify_fail("你的「拨云锁雾」不够娴熟，不能使用「云雾暗点」。\n");

        if( (int)me->query_skill("biyun-xinfa",1) < 100)
                return notify_fail("你的心法不够熟练！\n");

        if( query("neili", me)<800 )
                return notify_fail("你的内力不够。\n");

        ap = attack_power(me, "hand") + me->query_dex()*10;
        dp = defense_power(target, "dodge") + target->query_dex()*10;

        msg = HIG "$N手腕一翻，信手一个拈花诀，内力暗吐，“嗤”的一声，破空而去!\n"NOR;

        message_combatd(msg, me, target);

        addn("neili", -500, me);

        if (ap / 2 + random(ap) > dp)
        {
                if (! target->is_busy())
                        target->start_busy(ap/90 +2);
                msg = HIC "$n全身顿觉一麻，似乎不能动弹。\n"NOR;
        }
        else
        {
                me->start_busy(2);
                msg = HIM "只见$n侧身一让，一阵风声，破空而过！\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
