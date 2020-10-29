// kuang.c 风扫落叶

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIG "风扫落叶" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对！\n");

        if( query("neili", me)<180 )
                return notify_fail("你的真气不够，无法施展" + name() + "！\n");

        if ((int)me->query_skill("kuangfeng-jian", 1) < 100)
                return notify_fail("你的狂风剑法还不到家，无法施展" + name() + "！\n");

        if ((int)me->query_skill("dodge", 1) < 100)
                return notify_fail("你的轻功修为不足，无法施展" + name() + "！\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "大喝一声，手中的" + weapon->name() +
              HIC "犹如狂风疾电一般劈刺向$n" HIC "！\n"
              HIR "霎时间只见剑气层层叠叠如波浪般汹涌而起，$n"
              HIR "只觉得呼吸登时不畅。\n" NOR;
        message_combatd(msg, me, target);
        addn("neili", -150, me);

        count = me->query_skill("sword") / 2;
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (! target->is_busy() && random(2) == 1)
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(3));
        return 1;
}
