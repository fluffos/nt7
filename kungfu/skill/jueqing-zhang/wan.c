#include <ansi.h>
#include <combat.h>

#define WAN "「" HIW "万念俱灰" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(WAN "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(WAN "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if ((int)me->query_skill("jueqing-zhang", 1) < 100)
                return notify_fail("你绝情掌不够娴熟，难以施展" WAN "。\n");

        if (me->query_skill_mapped("strike") != "jueqing-zhang")
                return notify_fail("你没有激发绝情掌，难以施展" WAN "。\n");

        if (me->query_skill_prepared("strike") != "jueqing-zhang")
                return notify_fail("你没有准备绝情掌，难以施展" WAN "。\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("你的轻功修为不够，难以施展" WAN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在的真气不够，难以施展" WAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");

        msg = HIC "\n$N" HIC "一声长啸，声音震耳欲聋，悲痛欲绝，顿"
              "感万念俱灰，猛然间双掌疯狂般的拍向$n，看似杂乱无章，"
              "但内中却隐藏无限杀机。\n" NOR;
        message_sort(msg, me, target);
        
        if (random(ap) > dp / 2)
        {
                msg = HIR "$n" HIR "心神惧裂，一时间竟无从应对，"
                      "竟被困在$N" HIR "的掌风之中。\n" NOR;

                target->start_busy(ap / 90 + 2);
                       me->start_busy(1);
                addn("neili", -80, me);
        } else
        {
                msg = CYN "$n" CYN "看破$N" CYN "毫无攻击之意，于"
                      "是大胆反攻，将$N" CYN "这招尽数化解。\n" NOR;

                me->start_busy(2);
                addn("neili", -30, me);
        }
        message_vision(msg, me, target);

        return 1;
}