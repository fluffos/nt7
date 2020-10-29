// This program is a part of NT MudLIB
#include <ansi.h>
#include <combat.h>

string name() { return HIW "飞剑诀" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg, wn;
        object weapon;
        int level;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "sword")
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if ((int)me->query_skill("xiaoyao-jian", 1) < 60)
                return notify_fail("你逍遥剑法不够娴熟，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "xiaoyao-jian")
                return notify_fail("你没有激发逍遥剑法，难以施展" + name() + "。\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("你的轻功修为不够，难以施展" + name() + "。\n");

        if ((int)query("neili", me) < 200)
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        wn = weapon->name();

        msg = HIC "\n$N" HIC "陡然身法奇快，剑法灵动无比，手中" + wn + HIC "犹"
              "如脱手飞旋一般，将$n" HIC "周身笼罩。\n" NOR;

        message_combatd(msg, me, target);

        level = me->query_skill("sword");

        addn("neili", -120, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIY "$N" HIY "看不出$n" HIY "招式中的虚实，连忙"
                      "护住自己全身，一时竟无以应对！\n" NOR;
                target->start_busy(ap/90 + 2);
                me->start_busy(1);
        } else
        {
                msg = CYN "可是$N" CYN "镇定自若，小心拆招，没有被"
                      "$n" NOR + CYN "招式所困。\n" NOR;

                me->start_busy(2);
        }
        message_combatd(msg, target, me);

        return 1;
}