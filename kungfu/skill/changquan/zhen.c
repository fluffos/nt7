// gladiator

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "八震字决" NOR; }

int perform(object me, object target)
{
        string msg;
        int i;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name()+"只能空手施展。\n");

        if ((int)me->query_skill("changquan", 1) < 80)
                return notify_fail("你太祖长拳不够娴熟，难以施展"+name()+"。\n");

        if (me->query_skill_mapped("cuff") != "changquan")
                return notify_fail("你没有激发太祖长拳，难以施展"+name()+"。\n");

        if (me->query_skill_prepared("changquan") != "changquan")
                return notify_fail("你没有准备太祖长拳，难以施展"+name()+"。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在真气不足，难以施展"+name()+"。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "霎时间只见$N" HIY "跨立马步，稳定下盘，双拳有章有法的依次击向$n"
              HIY "全身各处。\n" NOR;
        message_combatd(msg, me, target);
        addn("neili", -50, me);

        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->start_busy(1 + random(3));
        return 1;
}