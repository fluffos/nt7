// fengyun. 风起云涌

#include <ansi.h>

inherit F_SSERVER;

string name() { return "风起云涌"; }
int perform(object me, object target)
{
        string msg;
        object weapon;
        int i;
        int skill;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「风起云涌」只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你只有空手才能使用「风起云涌」。\n");

        skill = me->query_skill("fengyun-bianhuan", 1);

        if (skill < 150)
                return notify_fail("你的风云变幻修为太低，现在不能使用「风起云涌」！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真气不够，无法使出「风起云涌」！\n");

        msg = HIW "$N" HIW "双拳一错，幻化出一圈圈似有若无，虚实难分的拳影，"
              HIW "，猱身向$n" HIW "打出。\n" NOR;

        message_combatd(msg, me, target);
        count = skill / 3;
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))  break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(3));
        addn_temp("apply/attack", -count, me);

        return 1;
}
