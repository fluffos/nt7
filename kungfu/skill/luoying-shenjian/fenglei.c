// This program is a part of NITAN MudLIB
// fenglei.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "风雷四神剑"; }

int perform(object me, object target)
{
        string msg, msg1;
        int i, count;
        object weapon;

        if (! target) target = offensive_target(me);
        if (! target || ! me->is_fighting(target))
                return notify_fail("「风雷四神剑」只能在战斗中对对手使用。\n");

        weapon=query_temp("weapon", me);
        if( !weapon || query("skill_type", weapon) != "sword"
        ||  me->query_skill_mapped("sword") != "luoying-shenjian")
                return notify_fail("你必须使用在剑时才能使出「风雷四神剑」！\n");

        if ((int)me->query_skill("luoying-shenjian", 1) < 80)
                return notify_fail("你的落英神剑不够娴熟，不会使用「风雷四神剑」。\n");

        if ((int)me->query_skill("bibo-shengong", 1) < 60)
                return notify_fail("你的碧波神功修为不够，不能使用「风雷四神剑」。\n");

        if ((int)me->query_dex() < 30)
                return notify_fail("你的身法太低，不能使用「风雷四神剑」。\n");

        if (me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("你使用的内功不对，不能使用「风雷四神剑」。\n");

        if( query("neili", me)<400 )
                return notify_fail("你现在内力太弱，不能使用「风雷四神剑」。\n");

        i = (me->query_skill("luoying-shenjian", 1) / 4);

        msg = HIG "$N高声长吟：“桃花影里飞神剑”，如风如雷般的发出数剑! \n" NOR;

        count = attack_power(me, "sword")/10;
        addn_temp("apply/damage", count*2, me);
        addn_temp("apply/str", count/10, me);
        addn_temp("apply/attack", count, me);
        message_combatd(msg, me, target);

        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        message_combatd(WHT"                                                                           风字诀\n"NOR,me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        message_combatd(HIC"                                                                           雨字诀\n"NOR,me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        message_combatd(MAG"                                                                           雷字诀\n"NOR,me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        message_combatd(HIR"                                                                           电字诀\n"NOR,me);
        addn("neili", -200, me);

        me->start_busy(2);
        addn_temp("apply/damage", -count*2, me);
        addn_temp("apply/str", -count/10, me);
        addn_temp("apply/attack", -count, me);

        return 1;
}
