// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "星光点点"; }

int perform(object me, object target)
{
        string msg;
        int i, ap, dp;

        i = me->query_skill("xingyi-zhang", 1)/5;
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「星光点点」只能在战斗中对对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("使用「星光点点」时双手必须空着！\n");

        if( (int)me->query_skill("xingyi-zhang", 1) < 120 )
                return notify_fail("你的星移掌不够娴熟，不会使用「星光点点」。\n");

        if( (int)me->query_skill("zihui-xinfa", 1) < 120 )
                return notify_fail("你的神元功等级不够，不能使用「星光点点」。\n");

        if( (int)me->query_dex() < 25 )
                return notify_fail("你的身法不够强，不能使用「星光点点」。\n");

        if (me->query_skill_prepared("strike") != "xingyi-zhang"
                || me->query_skill_mapped("strike") != "xingyi-zhang")
                return notify_fail("你现在无法使用「星光点点」进行攻击。\n");


        if( query("neili", me)<700 )
                return notify_fail("你现在内力太弱，不能使用「星光点点」。\n");

        addn("neili", -300, me);

        message_combatd(HIW "\n$N双掌交相呼应,漫天的掌影犹如星星般在$n周围闪烁不定！\n" NOR,me, target);


        addn_temp("apply/attack", i, me);
        addn_temp("apply/unarmed_damage", i, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        if( (int)me->query_str() >(int)target->query_str()/2)
        {
                addn_temp("apply/str", i, me);
                addn_temp("apply/attack", i, me);
                addn_temp("apply/damage", i, me);
                msg =  HIW"$N将神元神功发挥到极限，一双手掌发出耀眼的光芒，幻化出漫天掌影！" NOR;
                message_combatd(msg, me, target);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
                addn("neili", -100, me);
                addn_temp("apply/str", -i, me);
                addn_temp("apply/attack", -i, me);
                addn_temp("apply/damage", -i, me);
        }
        addn("neili", -400, me);
        addn_temp("apply/unarmed_damage", -i, me);

        addn_temp("apply/attack", -i, me);
        me->start_busy(1+random(2));
        return 1;
}
