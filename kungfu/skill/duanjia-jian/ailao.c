// ailao.c 哀牢山剑意

#include <ansi.h>

inherit F_SSERVER;

string name() { return "哀牢山剑意"; }

int perform(object me, object target)
{
        object weapon;
        int i, a;

        if (!target) target=offensive_target(me);

        if (!target
                || !target->is_character()
                || !me->is_fighting(target))
                return notify_fail("你不在战斗中！\n");

        weapon=query_temp("weapon", me);
        if( !objectp(weapon) || query("skill_type", weapon) != "sword" )
                return notify_fail("你手中无剑，如何使得出哀牢山剑意？\n");

        if (me->query_skill("kurong-changong", 1)<150)
                return notify_fail("你的内功火候未到，无法驾驭哀牢山剑意！\n");

        if (me->query_skill("sword", 1) < 150)
                return notify_fail("你剑法修为不够，无法施展哀牢山剑意！\n");

        if (me->query_skill("duanjia-jian",1)<150)
                return notify_fail("你段家剑修为不够，无法施展哀牢山剑意！\n");

        if( me->query_skill_mapped("force") != "kurong-changong")
                return notify_fail("你所用的内功与哀牢山剑意气路相悖！\n");

        if( query("neili", me) <= 500 )
                return notify_fail("你的内力不够使用哀牢山剑意！\n");

        message_vision(HIR "\n突然间$N剑法突变，剑气纵横，上六剑，下六剑，前六剑，后六剑，左六剑，\n\n"NOR, me, target);
        message_vision(HIR "\n右六剑，施展哀牢山剑意对$n虚虚实实连刺了三十六剑！\n\n" NOR, me, target);

        if( query("combat_exp", me)*10/query("combat_exp", target)<12 )
                a=3;
        else {
                if( query("combat_exp", me)*10/query("combat_exp", target)<15 )
                        a=4;
                else {
                        if( query("combat_exp", me)*10/query("combat_exp", target)<18 )
                                a=5;
                        else a=6;
                }
        }

        for (i=1; i<=a; i++)
                COMBAT_D->do_attack(me, target, weapon);


        if (a>4)
        {
                me->start_busy(a-random(3));
        } else
                me->start_busy(1);

        addn("neili", -200, me);

        return 1;
}