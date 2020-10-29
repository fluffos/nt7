//duan.c 
// gladiator

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int str, dex, skill, power;
        string weapon;

        if( !target ) target = offensive_target(me);

        if( userp(me) && !query("can_perform/qingyun-bian/duanyun", me) )
                return notify_fail("你所使用的外功中没有这样的功能。\n");
        
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("[断云决]只能对战斗中的对手使用。\n");


        if( me->query_skill("force") < 100 )
        return notify_fail("你的基本内功火候未到，无法施展断云决！\n");

        if( me->query_skill("whip") < 80 )
        return notify_fail("断云决需要精湛的青云鞭法方能有效施展！\n");

        // for a 800K player, frce/2 = 150, shen/3K = 300, power = 300
        // for players > 1.2M, power will hit max

        str = me->query_str();

        power=random(me->query_skill("qingyun-bian",1)/3)+query("force", me)/2;


        if(power<150)power=150;
        if(power>480)power=480;

        if( query("neili", me) <= 200 )
                return notify_fail("你的内力不够使用断云决！\n");

        message_vision(HIW "$N运足内力，猛地一扬"NOR + "$n" + 
                       HIW "卷起无边风云遮月掩日，一股"NOR + 
                       HIM "罡风" NOR + HIW "随著漫天鞭影扑天盖地的向敌人袭来。\n" 
                         NOR,me,query_temp("weapon", me));

        addn_temp("apply/attack", power/10, me);
        addn_temp("apply/damage", power/10, me);
        addn_temp("apply/armor", -power/5, target);
        addn_temp("apply/dodge", -power/5, target);

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        
        if( random(10)>5)COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        if( random(10)>8)COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        
        me->start_perform(1 + random(2),"[断云决]");
        
        addn_temp("apply/attack", -power/10, me);
        addn_temp("apply/damage", -power/10, me);
        addn_temp("apply/armor", power/5, target);
        addn_temp("apply/dodge", power/5, target);

        addn("neili", -power*2, me);
        me->start_busy( 2 + random(2));

        return 1;
}
