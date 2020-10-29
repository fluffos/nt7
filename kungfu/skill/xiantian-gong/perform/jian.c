#include <ansi.h>
#include <combat.h>

string name() { return HIW "先天功" HIR "乾阳" HIY "剑气" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, i, damage;
        string msg;
        int delta;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 280)
                return notify_fail("你的先天功修为不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("sun-finger", 1) < 280)
                return notify_fail("你一阳指诀不够娴熟，难以施展" + name() + "。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "xiantian-gong")
                return notify_fail("你没有激发先天功为拳脚，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("你没有激发先天功为内功，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "sun-finger")
                return notify_fail("你没有激发一阳指为指法，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "xiantian-gong"
           && me->query_skill_prepared("finger") != "sun-finger")
                return notify_fail("你没有准备先天功和一阳指，难以施展" + name() + "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "霎时只见$N" HIY "逆运" HIW "先天真气" HIY "，化为" HIR
              "纯阳内劲" HIY "聚于指尖，以一阳指诀手法疾点$n" HIY "全身诸"
              "多要穴。\n" NOR;

        ap = attack_power(me, "force") + me->query_skill("finger") +
             me->query_skill("unarmed");
        dp = defense_power(target, "force") + target->query_skill("dodge") +
             target->query_skill("parry");

        delta = ABILITY_D->check_ability(me, "ap_power-xtg-jian"); // 门派ab
        if( delta ) ap += ap*delta/100;
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "force");
                damage = damage_power(me, "finger");
                damage+= query("jiali", me);
                delta = ABILITY_D->check_ability(me, "da_power-xtg-jian"); // 门派ab
                if( delta ) damage += damage*delta/100;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 300,
                                           HIR "$n" HIR "只觉全身一热，$P" HIR "「"
                                           HIW "先天功" HIR "乾阳" HIY "剑气" HIR
                                           "」顿时破体而入，便似身置洪炉，喷出一口"
                                           "鲜血。\n" NOR);
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "$n" CYN "见$N" CYN "这指来势汹涌，不敢"
                       "轻易招架，当即飞身纵跃闪开。\n" NOR;
                message_combatd(msg, me, target);
        }

        msg = HIR "紧接着$N" HIR "十指纷飞，接连弹出数道无形剑气，$n" HIR "四面八"
              "方皆被剑气所笼罩。\n"NOR;
        message_combatd(msg, me, target);

        addn_temp("apply/attack", ap/10, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, TYPE_LINK);
        }

        addn_temp("apply/attack", -ap/10, me);
        addn("neili", -600, me);
        me->start_busy(2 + random(3));
        return 1;
}
