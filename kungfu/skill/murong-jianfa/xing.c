// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "剑转七星" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, i;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("murong-jianfa", 1) < 80)
                return notify_fail("你的慕容剑法不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "murong-jianfa")
                return notify_fail("你没有激发慕容剑法，难以施展" + name() + "。\n");

        if ((int)me->query_skill("dodge") < 120)
                return notify_fail("你的轻功修为不够，无法施展" + name() + "！\n");

        if( query("neili", me)<200 )
                return notify_fail("你目前的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIM "$N" HIM "使出慕容家绝技「" HIW "剑转七星" HIM "」，手中"
              + weapon->name() + HIM "暗合北斗七星方位，忽伸忽缩，变化莫测！\n" NOR;

        addn("neili", -210, me);

        message_combatd(msg, me, target);

        for (i = 0; i < 7; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (! target->is_busy() && random(2) == 1)
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 13);
        }

        me->start_busy(1 + random(3));

        return 1;
}
