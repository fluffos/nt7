#include <ansi.h>

inherit F_SSERVER;

string name() { return "乱拳飞舞"; }

int perform(object me, object target)
{
        object weapon;
        int damage,skill,wap,wdp;
        string *limb, result, str,msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("乱拳飞舞只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("空手才能施展乱拳飞舞！\n");

        if( me->query_skill_mapped("unarmed") != "kongming-quan" )
                return notify_fail("你所用的并非空明拳，不能施展乱拳飞舞！\n");

        if( me->query_skill_prepared("unarmed") != "kongming-quan" )
                return notify_fail("你所备的并非空明拳，不能施展乱拳飞舞！\n");

        /*
        if( me->query_skill_mapped("force") != "xiantian-gong" )
                return notify_fail("你所用的并非先天功，施展不出乱拳飞舞！\n");
        */

        if( me->query_skill("force") < 120 )
                return notify_fail("你的先天功火候未到，无法施展乱拳飞舞！\n");

        if( me->query_skill("unarmed") < 120 )
                return notify_fail("乱拳飞舞需要精湛的空明拳方能有效施展！\n");

        if( query("max_neili", me) <= 1000 )
                return notify_fail("你的内力等级不够使用乱拳飞舞！\n");

        if( query("neili", me) <= 1000 )
                return notify_fail("你的内力不够，无法继续施展乱拳飞舞！\n");

        msg = HIY"$N张口一声暴喝，双目精光四射，接着身形飘忽不定，双拳幻化出漫天拳影重重向$n笼罩过去！\n\n"NOR;
        message_combatd(msg, me, target);

        skill =  me->query_skill("unarmed");

        addn_temp("apply/unarmed_damage", skill/2, me);
        addn_temp("apply/attack", skill/2, me);

        message("vission",HIR  "上一拳！\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me), 3);
        message("vission",HIR  "下一拳！\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me), 3);
        message("vission",HIR  "左一拳！\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me), 3);
        message("vission",HIR  "右一拳！\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me), 3);
        message("vission",HIR  "前一拳！\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me), 3);
        message("vission",HIR  "后一拳！\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me), 3);
        message("vission",HIR  "最后再一拳！\n" NOR,environment(me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me), 3);
        me->start_busy(3);

        addn_temp("apply/unarmed_damage", -skill/2, me);
        addn_temp("apply/attack", -skill/2, me);

        addn("neili", -skill, me);

        return 1;
}
