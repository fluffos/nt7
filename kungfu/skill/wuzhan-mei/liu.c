// This program is a part of NT MudLIB
// liu.c 流花掠影

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "流花掠影"; }

int perform(object me, object target)
{
        int skill;
        object weapon;

        if((skill = me->query_skill("wuzhan-mei",1)) < 100)
                return notify_fail("你的五展梅剑法不够纯熟，无法使用『流花掠影』。\n");

        if( !target ) target = offensive_target(me);

        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("『流花掠影』只能对战斗中的对手使用。\n");

        if( query("neili", me)<400 )
                return notify_fail("你目前的内力不足，无法施展『流花掠影』。\n");

        if( !(weapon=query_temp("weapon", me)) || query("skill_type", weapon) != "sword"
        || me->query_skill_mapped("sword") != "wuzhan-mei")
                return notify_fail("你必须在使用剑时才能使出『流花掠影』。\n");

        addn("neili", -300, me);

        message_combatd(HIR"$N手中乱抖，幻出一片青光，施展出唐门绝学『流花掠影』。\n\n"NOR,me);

        addn_temp("apply/attack", skill/2, me);
        for(int i=0;i<5;i++)
        {
                // COMBAT_D->do_attack(me,target,TYPE_QUICK);
                COMBAT_D->do_attack(me,target, weapon, 0);
        }
        /*
        if( random(query("force", target))<query("force", me)/2 )
        {
                target->apply_condition("weapon_bleeding", 5+random(3));
        }
        */
        addn_temp("apply/attack", -skill/2, me);
        me->start_busy(2);
        return 1;
}
