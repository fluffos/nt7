#include <ansi.h>
#include <combat.h>

#define QIAN "「" HIG "千山孤鸿影" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int attack_time, i;
        int skill;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(QIAN "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(QIAN "只能空手施展。\n");

        if ((int)me->query_skill("guhong-zhang", 1) < 80)
                return notify_fail("你孤鸿掌法不够娴熟，难以施展" QIAN "。\n");

        if (me->query_skill_mapped("strike") != "guhong-zhang")
                return notify_fail("你没有激发孤鸿掌法，难以施展" QIAN "。\n");

        if (me->query_skill_prepared("strike") != "guhong-zhang")
                return notify_fail("你没有准备孤鸿掌法，难以施展" QIAN "。\n");

        if (me->query_skill("force") < 100)
                return notify_fail("你的内功修为不够，难以施展" QIAN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在的真气不够，难以施展" QIAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
        
        skill = me->query_skill("guhong-zhang", 1);
        
        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        msg = HIC "\n$N" HIC "双掌陡然连续拍出，刚中带柔，一招"
              "「" HIG "千山孤鸿影" HIC "」，双掌带风，已将$n" 
              HIC "笼罩在掌风之中。\n" NOR;
        message_sort(msg, me, target);

        if (random(ap) > dp / 2)
        {
                msg = HIR "结果$n" HIR "目不暇接，顿时被$N" HIR "掌"
                      "风所困，顿时阵脚大乱。\n" NOR;
                addn_temp("apply/attack", skill/2, me);
        } else
        {
                msg = HIY "$n" HIY "看清$N" HIY "这几招的来路，但"
                      "内劲所至，刚柔并济，也只得小心抵挡。\n" NOR;          
        }
        message_vision(msg, me, target);

        attack_time += 3 + random(ap / 40);

        if (attack_time > 6)
                attack_time = 6;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->start_busy(1 + random(attack_time));
        addn_temp("apply/attack", -skill/2, me);

        return 1;
}