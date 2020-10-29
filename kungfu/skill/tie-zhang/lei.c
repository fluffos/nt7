#include <ansi.h>
#include <combat.h>

string name() { return HIR "掌心雷" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;
        int fmsk = me->query_skill("tiezhang-shuishangpiao", 1);

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("tie-zhang", 1) < 160)
                return notify_fail("你铁掌掌法火候不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "tie-zhang")
                return notify_fail("你没有激发铁掌掌法，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "tie-zhang")
                return notify_fail("你没有准备铁掌掌法，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 240)
                return notify_fail("你的内功修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("你的内力修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = WHT "$N" WHT "运转真气施出「" HIR "掌心雷" NOR +
              WHT "」绝技，双掌翻红，有如火烧，朝$n" WHT "猛"
              "然拍出。\n" NOR;

        ap=attack_power(me,"strike")+me->query_str()*10;
        dp=defense_power(target,"parry")+target->query_con()*10;

        if (ap / 2 + random(ap) + fmsk > dp)
        {
                damage = damage_power(me,"strike");
                damage+= query("jiali", me);
                damage+= fmsk/3;
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 85 + fmsk / 10,
                                           HIR "结果只听$n" HIR "一声闷哼，被$N"
                                           HIR "一掌劈个正着，口中鲜血狂喷而出。"
                                           "\n" NOR);
                addn("neili", -250, me);
                me->start_busy(2);
        } else
        {
                msg += CYN "$n" CYN "眼见$N" CYN "来势汹涌，丝毫"
                       "不敢小觑，急忙闪在了一旁。\n" NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}