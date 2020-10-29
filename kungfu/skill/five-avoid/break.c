// break.c 五遁绝杀

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int count;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「五遁绝杀」只能在战斗中使用。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的气不够，无法施展「五遁绝杀」！\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的内功火候不够，难以施展「五遁绝杀」！\n");

        if( query("neili", me)<query("max_neili", me)/2 )
                return notify_fail("你的真气不够，无法施展「五遁绝杀」！\n");

        msg = HIC "$N" HIC "使出五行遁中的「五遁绝杀」，身法"
              "陡然间变得变幻莫测！\n" NOR;

        message_combatd(msg, me);
        count = (int)me->query_skill("five-avoid") / 30 + 2;
        if (count > 5 ) count = 5;

        while (count--)
        {
                if (! target || (environment(target) != environment(me)) ||
                    ! me->is_fighting(target) ||
                    query("qi", me)<20 || 
                    query("neili", me)<20 )
                {
                        message_combatd(WHT "$N" WHT "的身形倏地一"
                                        "转，收身停住了脚步。\n" NOR, me);
                        break;
                } else

                message_combatd(WHT "$N" WHT "的身影在$n"
                                WHT "身旁时隐时现 ...\n" NOR, me, target);
                if (! COMBAT_D->fight(me, target))
                        message_combatd(WHT "但是$N" WHT "始终没有找到机会出手！\n" NOR, me);
                me->receive_damage("qi", 10);
                addn("neili", -10, me);
        }

        me->start_busy(1);
        return 1;
}