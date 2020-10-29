// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "真·般若极" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp;
        int damage;
        int i, count;
        string msg;
        int fmsk = me->query_skill("mizong-zhenyan", 1);
        int delta;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("longxiang-gong", 1) < 390)
                return notify_fail("你的龙象般若功修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<7000 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "longxiang-gong")
                return notify_fail("你没有激发龙象般若功为拳脚，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "longxiang-gong")
                return notify_fail("你没有激发龙象般若功为内功，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "longxiang-gong")
                return notify_fail("你没有准备使用龙象般若功，难以施展" + name() + "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "仰天一声怒嚎，将龙象般若功提运至极限，全身顿时罡劲"
              "迸发，真气蒸腾而出，笼罩$N" HIY "\n四方！电光火石间，$N" HIY "双"
              "拳已携着雷霆万钧之势崩击而出，卷起万里尘埃，正是密宗绝学：\n" NOR;

        msg += HIW
        "        般      般般般           若        若           极    极极极极极极\n"
        "    般般般般    般  般       若若若若若若若若若若       极       极    极\n"
        "    般    般    般  般           若        若       极极极极极  极    极\n"
        "    般 般 般 般般    般般          若                 极极极  极极极 极极极\n"
        "  般般般般般般             若若若若若若若若若若若若  极 极 极  极极     极\n"
        "    般    般   般般般般         若                   极 极 极  极 极   极\n"
        "    般 般 般    般  般        若 若若若若若若若      极 极 极 极   极极\n"
        "    般    般     般般       若   若          若         极   极     极\n"
        "   般    般   般般  般般         若若若若若若若         极  极  极极极极极\n\n" NOR;

        msg += HIY "$N" HIY "一道掌力打出，接着便涌出了第二道、第三道掌力，掌势"
               "连绵不绝，气势如虹！直到$N" HIY "\n第十三道掌力打完，四周所笼罩"
               "着的罡劲方才慢慢消退！而$n" HIY "此时却已是避无可避！\n\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_con()*10;
        dp = defense_power(target, "parry") + target->query_dex()*10;
        
        delta = ABILITY_D->check_ability(me, "ap_power-lxg-zhen"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        if (ap / 2 + random(ap) > dp)
        {
                if ( query("max_neili",me) / 2 > query("max_neili",target) ) 
                {
                        msg += HIR "$n" HIR "全然无力阻挡，竟被$N"
                                HIR "一拳击得飞起，重重的跌落在地上。\n" NOR;
                        addn("neili", -50, me);
                        me->start_busy(1);

                        message_combatd(msg, me, target);
                        target->unconcious(me);

                        me->start_busy(1);
                        return 1;
                } else
                {
                        damage = damage_power(me, "unarmed");
                        damage+= query("jiali", me);
                        damage *= 2;
                        
                        delta = ABILITY_D->check_ability(me, "da_power-lxg-zhen"); // 门派ab
                        if( delta ) damage += damage*delta/100;
        
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 200+fmsk / 20,
                                                   HIR "$n" HIR "不及闪避，顿被$N" HIR
                                HIR "一拳击得飞起，重重的跌落在地上。\n" NOR);
                        count = ap / 10;
                        msg += HIR "$n" HIR "被$p" HIR "罡劲所逼，一时无力作出抵挡，竟呆立当场。\n" NOR;
                }
        } else
        {
                msg += HIY "$n" HIY "见$p" HIY "来势迅猛之极，甚难防备，连"
                       "忙振作精神，小心抵挡。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count, me);

        addn("neili", -300, me);

        for (i = 0; i < 5 + fmsk / 100; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, TYPE_LINK);
        }

        me->start_busy(1 + random(3));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/unarmed_damage", -count, me);

        return 1;
}
