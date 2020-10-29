// by darken@SJ

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

string perform_name(){ return HBBLU"入 白 刃"NOR; }
int perform(object me, object target)
{
        int skill;
        object weapon;
        skill = (int)me->query_skill("super-strike", 1);
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("入白刃只能在战斗中使用。\n");
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「入白刃」！\n");   
        if( skill < 150 )
                return notify_fail("你的铁掌掌法不够娴熟，使不出「入白刃」。\n");
        if(me->query_skill("force",1) < 150 )
                return notify_fail("你的归元吐呐法不够娴熟，使不出「入白刃。\n");
        if(me->query_skill_mapped("strike") != "super-strike" )
               return notify_fail("你现在无法使用「入白刃」！\n");
        if( (int)me->query("max_neili") < 2000)
                return notify_fail("你现在内力太弱，使不出「入白刃」。\n");      
        if( (int)me->query("neili") < 1500 )
                return notify_fail("你现在真气太弱，使不出「入白刃」。\n");
        weapon = target->query_temp("weapon");
        if (!weapon)
                return notify_fail("对手没有兵器，你要夺他的手吗？\n");      

        message_vision(HBBLU"\n$N左掌向他脸上拍去。$n忙举起"NOR+weapon->name()+HBBLU"挡格。\n"NOR,me,target);
        if (random(me->query_str()) > target->query_str()/2) {
           message_vision(HIR"\n$N变招快极，左手下压，已抓住"+weapon->name()+HIR"！\n"NOR,me,target);
           message_vision(HIR"$N掌缘甫触"+weapon->name()+HIR"，尚未抓紧，已向里夺！\n"NOR,me,target);
           if (random(me->query_str()) > target->query_str()/4) {
              message_vision(HIR"$n手中的"+weapon->name()+HIR"已被$N硬生生的夺去了！\n"NOR,me,target);
              weapon->move(me);
              target->reset_action();
           } else
              message_vision(HIR"只是$N力量不如$n，无法将$n的"+weapon->name()+HIR"夺过。\n"NOR,me,target);
           target->start_busy(2);
        } else
           message_vision(HIR"\n$n"+weapon->name()+HIR"陡然转向，$N急忙收手。\n"NOR,me,target);
        me->start_perform(3,"「入白刃」");
        return 1;
}

