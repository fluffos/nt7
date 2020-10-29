// This program is a part of NITAN MudLIB
// lei.c 迅雷

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "迅雷"; }

int perform(object me, object target)
{
        string msg;
        int j, z;
        object weapon;

        j = me->query_skill("xuantie-jian", 1);
        z = me->query_skill("surge-force", 1);

        weapon=query_temp("weapon", me);

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「迅雷」只能在战斗中对对手使用。\n");

       if( !weapon || query("skill_type", weapon) != "sword" )
                return notify_fail("你必须在使用剑时才能使出「迅雷」！\n");

        if (me->query_skill_mapped("parry") != "xuantie-jian")
                return notify_fail("你的基本招架必须是玄铁剑法时才能使出「迅雷」！\n");

        if(me->query_skill("xuantie-jian", 1) < 160 )
                return notify_fail("你的玄铁剑法还不够娴熟，使不出「迅雷」。\n");

        if(me->query_skill("surge-force", 1) < 160 )
                return notify_fail("你的怒海狂涛修为不够，使不出「迅雷」。\n");

        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("你的内功等级不够，使不出「迅雷」。\n");

        if( (int)me->query_str() < 32)
                return notify_fail("你的膂力还不够，使不出「迅雷」。\n");

        if( (int)me->query_dex() < 30)
                return notify_fail("你的身法还不够，使不出「迅雷」。\n");

        if( query("max_neili", me)<1800 )
                return notify_fail("你现在内力太弱，使不出「迅雷」。\n");

        if( query("neili", me)<900 )
                return notify_fail("你现在真气太弱，使不出「迅雷」。\n");

        addn_temp("apply/str", z/6, me);
        addn_temp("apply/attack", j/6, me);
        addn_temp("apply/damage", z/2, me);

        msg = BLU "\n$N将手中的"+weapon->name()+"缓缓向$n一压，忽然剑光一闪， 一剑幻为四剑，宛如奔雷掣电攻向$n！\n\n"NOR;
        message_combatd(msg, me, target);

        COMBAT_D->do_attack(me,target,query_temp("weapon", me),3);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),3);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),3);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),3);

        addn("neili", -500, me);

        addn_temp("apply/str", -z/6, me);
        addn_temp("apply/attack", -j/6, me);
        addn_temp("apply/damage", -z/2, me);

        me->start_busy(2);
        if( !target->is_busy() )
                target->start_busy(1);
        return 1;
}
