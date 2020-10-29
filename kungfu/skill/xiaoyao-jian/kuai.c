// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIM "快剑诀" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int i, attack_time;
        int level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = query_temp("weapon", me))
           || (string)query("skill_type", weapon) != "sword")
                return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("xiaoyao-jian", 1) < 120)
                return notify_fail("你的逍遥剑法不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "xiaoyao-jian")
                return notify_fail("你没有激发逍遥剑法，难以施展" + name() + "。\n");

        if (query("neili", me) < 300)
                return notify_fail("你目前的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "\n$N" HIW "蓦的一声清啸，施出绝学「" HIM "快剑诀"
              HIW "」，手中" + weapon->name() + HIW "呼呼作响。霎时间"
              "奇妙的剑招连绵涌出。" NOR;

        attack_time = 4;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        level = me->query_skill("xiaoyao-jian", 1)/3;
        attack_time += random(ap / 120);

        if (attack_time > 9)
                attack_time = 9;

        addn("neili", -attack_time*30, me);
        addn_temp("apply/attack", level, me);

        message_combatd(msg, me, target);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (! target->is_busy() && random(3) == 1)
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(attack_time));
        addn_temp("apply/attack", -level, me);

        return 1;
}