// This program is a part of NITAN MudLIB
// sanjue.c  达摩剑 达摩三绝剑

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "达摩三绝剑"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int skill;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「达摩三绝剑」只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if (me->query_dex() < 30)
                return notify_fail("你的身法不够，目前还不能使用这项绝技！\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的内功的修为不够，不能使用这一绝技！\n");

        if (me->query_skill("dodge") < 200)
                return notify_fail("你的轻功修为不够，不能使用达摩三绝剑！\n");

        if (me->query_skill("sword") < 200)
                return notify_fail("你的剑法修为不够，目前不能使用达摩三绝剑！\n");

        if( query("neili", me)<150 )
                return notify_fail("你的真气不够，不能使用达摩三绝剑！\n");

        if (me->query_skill_mapped("sword") != "damo-jian")
                return notify_fail("你没有激发达摩剑，不能使用达摩三绝剑！\n");

        msg = HIC "$N" HIC "使出达摩剑的绝技「达摩三绝剑」，身法陡然加快！\n" NOR;
        message_combatd(msg, me);

        addn("neili", -75, me);
        
        skill = me->query_skill("damo-jian", 1)/2;
        // The first attack
        addn_temp("apply/attack", skill, me);
        COMBAT_D->do_attack(me, target, weapon, TYPE_LINK);

        // The second attack
        addn_temp("apply/attack", skill, me);
        COMBAT_D->do_attack(me, target, weapon, TYPE_LINK);

        // The third attack
        addn_temp("apply/attack", skill*2, me);
        COMBAT_D->do_attack(me, target, weapon, TYPE_LINK);

        // Back
        addn_temp("apply/attack", -skill*4, me);

        me->start_busy(1 + random(2));

        return 1;
}
