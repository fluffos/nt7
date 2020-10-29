// by darken@SJ

inherit F_SSERVER;
#include <ansi.h>

string perform_name(){ return HBBLU"黑 砂 掌"NOR; }
int perform(object me, object target)
{
        string msg;
        if( !target ) target = offensive_target(me);
        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("「黑砂掌」只能对战斗中的对手使用。\n");
        if( (int)me->query_skill("force", 1) < 150 )
                return notify_fail("你的归元吐纳法修为未到，无法使出黑砂掌。\n");
        if( (int)me->query_skill("dodge", 1) < 150 )
                return notify_fail("你的水上漂修为未到，无法使出黑砂掌。\n");
        if( (int)me->query_skill("super-strike", 1) < 150 )
                return notify_fail("你的铁掌修为未到，无法使出黑砂掌。\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("你现在内力太弱，不能出黑砂掌。\n");
        if (target->query_condition("no_force"))
                return notify_fail("他已经被击中了，不需要再使用黑砂掌。\n");
                
        me->start_perform(1,"黑砂掌");
        msg = HBBLU"\n$N双手一错，一上一下向$n的胸口及丹田击到！\n"NOR;
        if (random(me->query_dex()) > target->query_dex()/3 || random(me->query_con()) > target->query_con()/5)
        {
                msg += HIR"结果$N双双击中，$n真气一窒，内息再也无法自由运转！\n"NOR;
                me->start_busy(1);
                target->apply_condition("no_force",(int)me->query_skill("force")/30 + (int)me->query_skill("poison",1)/30);
        }
        else {
                me->start_busy(1);
                if (!target->is_busy()) target->start_busy(2);
                msg += HIR"$n勉强躲开，气息粗重。\n"NOR;
        }
        me->add("neili",-(300+random(100)));
        message_vision(msg, me, target);
        return 1;
}
