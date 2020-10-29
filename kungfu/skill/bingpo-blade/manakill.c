// This program is a part of NT MudLIB

#include <command.h>
#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
       string msg;
       int ski_value, max_lv;
       ski_value= random(me->query_skill("bingpo-blade",1));
       max_lv=me->query_skill("bingpo-blade",1);

        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("『魔气杀』只能对战斗中的对手使用。\n");
  
/*
        if( me->query_skill_mapped("blade")!="bingpo-blade" )
         return notify_fail("你没有装备冰破寒刀。 \n");
*/
   if( me->query_skill("bingpo-blade",1)<100 )
         return notify_fail("你的冰破寒刀技巧不足。 \n");

   if( me->query_skill("blade",1)<100 )
         return notify_fail("你的刀法不够好。 \n");
   if( query("neili", me)<1000 )
         return notify_fail("你的内力不够。\n");
   if( target->is_busy() )
      return notify_fail(target->name() + "为了躲避你的杀气,目前正自顾不暇!\n");
msg = HIY "$N自残己身,以血气转换成杀气。\n
            ……$N身上发出一股强大的杀气……\n
    ■$N身上杀气逐渐地聚集在双手,在双手上形成两团魔气■\n
            $N倏地大喝一声－－魔 气 杀－－\n\n" NOR;

     if( ski_value+50<random(max_lv) && query("combat_exp", me)>2000000){
     msg += HIR BLINK "$N突然喉头一动～～　只见$N口中喷出一道血柱往$n射去～～\n
此乃魔气杀之
            最终杀招 『魔 血 气 杀』\n\n
$n遭到前所未有的打击,但$N也受伤不轻。\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") / 20 + 3);
     target->receive_damage("qi",query("max_qi", target)*70/100);
     me->receive_damage("qi",query("qi", me)*30/100);
     addn("neili", -50, me);
     }
   else if( ski_value < 20 ){
      msg +="$N真气所转换的杀气不够大,对敌人毫无影响。\n";
      me->receive_damage("qi",query("qi", me)*1/100);
      addn("neili", -50, me);}
     
    
    else if( ski_value <  70 ){
     msg += HIM "第一招 『魔气无常』\n\n$n受到伤害,动弹不得！\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 1);

     addn("neili", -query("max_neili", me)*2/10, me);}
    
    else if( ski_value <  90 ){
     msg += HIG "第二招 『火魔煞神』\n\n$n受到伤害,动弹不得！\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 1);
 
     addn("neili", -query("max_neili", me)*3/10, me);}
     
     else  if( ski_value < 100 ){
     msg += HIC "第三招 『商魂魔身』\n\n$n受到伤害,动弹不得。\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 1);

     addn("neili", -query("max_neili", me)*4/10, me);}

     else if( ski_value <  120 ){
     msg += HIB "第四招 『剑魔灭世』\n\n$n受到伤害,动弹不得！\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 1);

     addn("neili", -query("max_neili", me)*5/10, me);}

     else if( ski_value <  140 ){
     msg += HIW "第五招 『狂魔破空』\n\n$n受到伤害,动弹不得！\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 2);

     addn("neili", -query("max_neili", me)*6/10, me);}


     else if( ski_value <  160 ){
     msg += CYN "第六招 『群魔乱舞』\n\n$n受到伤害,动弹不得！\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 2);

     addn("neili", -query("max_neili", me)*7/10, me);}

     else if( ski_value <  180 ){
     msg +=  YEL "第七招 『天极魔杀』\n\n$n受到伤害,动弹不得！\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 2);

     addn("neili", -query("max_neili", me)*8/10, me);}

     else if( ski_value <  200 ){
     msg += BLU "第八招 『斗魔无生魂』\n\n$n受到伤害,动弹不得！\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 2);

     addn("neili", -query("max_neili", me)*9/10, me);}

     else                    {
     msg += RED "第九招 『风魔狂转业』\n\n$n受到伤害,动弹不得。\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 2);
 
     addn("neili", -query("max_neili", me)*9/10, me);}

     message_vision(msg, me, target);
        return 1;
}