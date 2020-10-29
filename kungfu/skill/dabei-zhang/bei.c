#include <ansi.h>
#include <combat.h>

#define BEI "「" HIW "万里鲸涛大悲神诀" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int i, ap, dp;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(BEI "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(BEI "只能空手使用。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你内功修为不够，难以施展" BEI "。\n");

        if( query("max_neili", me)<3500 )
                return notify_fail("你内力修为不够，难以施展" BEI "。\n");

        if ((int)me->query_skill("dabei-zhang", 1) < 220)
                return notify_fail("你大悲神掌火候不够，难以施展" BEI "。\n");

        if (me->query_skill_mapped("strike") != "dabei-zhang")
                return notify_fail("你没有激发大悲神掌，难以施展" BEI "。\n");

        if (me->query_skill_prepared("strike") != "dabei-zhang")
                return notify_fail("你没有准备大悲神掌，难以施展" BEI "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在真气不够，难以施展" BEI "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "凄然一声长啸，施出「" HIG "万里鲸涛大悲神诀"
              HIW "」，双掌翻滚出漫天掌影，尽数拍向$n" HIW "。\n" NOR;  

        ap = attack_power(me, "strike") + me->query_int()*10;

        dp = defense_power(target, "force") + target->query_int()*10;

        if (ap / 2 + random(ap) > dp)
        { 
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                           HIR "$n" HIR "勘破不透掌中虚实，$N" HIR
                                           "双掌正中$p" HIR "前胸，“喀嚓喀嚓”接"
                                           "连断了数根肋骨。\n" NOR);
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "$n" CYN "见$N" CYN "这掌来势非凡，不敢"
                       "轻易招架，当即飞身纵跃闪开。\n" NOR;
                message_combatd(msg, me, target);
        }

        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn("neili", -300, me);
        me->start_busy(3 + random(3));
        return 1;
}
