// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "追魂爪" NOR; }

int perform(object me, object target)
{
        object weapon;
        int level;
        int i;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("只有空手才能施展" + name() + "。！\n");

        if (me->query_skill_mapped("claw") != "sanyin-zhua")
                return notify_fail("你所用的并非三阴蜈蚣爪，不能施展" + name() + "！\n");

        if (me->query_skill_prepared("claw") != "sanyin-zhua")
                return notify_fail("你所备的并非三阴蜈蚣爪，不能施展" + name() + "！\n");

        /*
        if (me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("你所用的并非化功大法，施展不出" + name() + "！\n");

        if ((int)me->query_skill("huagong-dafa", 1) < 120)
                return notify_fail("你化功大法修为太差，不能运用" + name() + "！\n");
        */

        if (me->query_skill("sanyin-zhua", 1) < 120)
                return notify_fail("你三阴蜈蚣爪修为太差，不能运用" + name() + "！\n");

        if( query("neili", me) <= 400 )
                return notify_fail("你的内力不够使用追魂爪！\n");

        message_combatd(HIB "$N忽然嘿嘿干笑几声，双袖狂舞卷起地上黄沙飞扬令人看不出要从何处出招，\n"
                        "突然$N尖叫一声，声未停影先至向着$n扑来，双爪连抓数爪，其速之快令$n无从躲闪。\n"
                        NOR, me, target);

        level = me->query_skill("sanyin-zhua", 1) + me->query_skill("finger", 1);
        level /= 4;

        addn_temp("apply/attack", level, me);
        addn_temp("apply/unarmed_damage", level, me);

        for (i = 0; i < 5 + random(5); i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, TYPE_LINK);
        }
        addn_temp("apply/attack", -level, me);
        addn_temp("apply/unarmed_damage", -level, me);

        me->start_busy(2 + random(2));
        return 1;
}
