
#include <ansi.h>

inherit F_SSERVER;
string name() { return "风云变色"; }

int perform(object me, object target)
{
        int skill,power;
        string weapon;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("风云变色只能对战斗中的对手使用。\n");


         /*
        if( me->query_skill_mapped("force") != "xiantian-gong" )
                 return notify_fail("你所用的并非玄门先天功，施展不出风云变色！\n");
         */

        if( me->query_skill("force") < 140 )
                return notify_fail("你的基本内功火候未到，无法施展风云变色！\n");

        if( me->query_skill("whip") < 135 )
                return notify_fail("风云变色需要精湛的断云鞭法方能有效施展！\n");

        if( !query_temp("weapon", me) || query("skill_type", query_temp("weapon", me)) != "whip" )
                return notify_fail("你并没有装备鞭作为武器。\n");

        power=random(query("neili", me)/50)+query("jiali", me)/2;
        if(power<150) power=150;
        if(power>1000) power=1000;

        if( query("neili", me) <= 200+power*2 )
                return notify_fail("你的内力不够使用风云变色！\n");

        message_combatd(HIW"$N运足内力，猛地一扬"NOR+"$n"+HIW"卷起无边风云遮月掩日，一股"NOR+HIM"罡风"NOR+HIW"随著漫天鞭影扑天盖地的向敌人袭来。\n\n"NOR,me,
                        query_temp("weapon", me));

        addn_temp("apply/attack", power/2, me);
        addn_temp("apply/damage", power/5, me);
        addn_temp("apply/armor", -power/2, target);
        addn_temp("apply/dodge", -power, target);

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        addn_temp("apply/attack", -power/2, me);
        addn_temp("apply/damage", -power/5, me);
        addn_temp("apply/armor", power/2, target);
        addn_temp("apply/dodge", power, target);

        addn("neili", -power*2, me);
        me->start_busy( 2+random(2));

        return 1;
}

