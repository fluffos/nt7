//Code of Shenzhou
//coding by Slow
#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_DBASE;
inherit F_SSERVER;

void remove_effect(object me);
void checking(int del_time,object me);

int exert(object me, object target)
{
          int lv;

          if( !query("canewhua", me))return notify_fail("你还没得到化功大法的真传。\n");

          /*
          if( query("family/family_name", me) != "星宿派" )
                  return notify_fail("化功大法是星宿派的独门绝学。\n");
          */

          if( query("no_fight", environment(me)) && file_name(environment(me)) != "/d/city/biwu_dating" )
                  return notify_fail("在这里不能运用化功大法。\n");

          lv = (int)me->query_skill("huagong-dafa", 1);

          if( target == me) target=offensive_target(me);
          if( !target ) target = offensive_target(me);
          if( !target ) target = me->select_opponent();

          if( query_temp("newhua", me) )
                    return notify_fail("你已经施展出化功大法了！\n");


          if( me->query_skill("huagong-dafa", 1) < 360 )
                    return notify_fail("你的化功大法火候未到！\n");

          if( me->query_skill_mapped("force") != "huagong-dafa")
                    return notify_fail("你所运使的内功并非化功大法，无法施展开来！\n");

          if( query("neili", me) <= 3000 )
                  return notify_fail("你的内力不足以施展化功大法！\n");

          if( query("jingli", me) <= 900 )
                  return notify_fail("你的精力不足以施展化功大法！\n");

          if( me->query_skill_mapped("sword") == "pixie-jian" ||
              me->query_skill_mapped("parry") == "pixie-jian" ||
              me->query_skill_mapped("dodge") == "pixie-jian" )
          return notify_fail("辟邪剑法与化功大法的修炼方法相悖，无法同时施展化功大法和辟邪剑法！\n");
          if(me->is_busy())
                  return notify_fail("你正忙着呢,没办法施展化功大法! \n");

message_vision(
HIB"$N突然面色阴暗下来，干笑几声，陡然加快身法，将一双大袖舞得呼呼风响。\n"
HIG"只见$N越舞越快满场游走，化功大法激发出的真气布满$N的两只袖袍，象鼓足的风帆。\n"
HIB"四处弥漫的真气将空气挤成一股股汹涌澎湃的气浪。\n" NOR, me, target );


          set_temp("newhua", me->query_skill("huagong-dafa",1)/20+10, me);
          call_out("checking", 0, 1, me);
          return 1;
}


void checking(int del_time,object me)
{
          int num,ap,dp,dmg,the_time;
         int exp_div;
          object target;

          if( !me || !query_temp("newhua", me))return ;
          target=query_temp("offensive_target", me);
          num=query_temp("newhua", me);

          if( me->query_skill_mapped("sword") == "pixie-jian" ||
              me->query_skill_mapped("parry") == "pixie-jian" ||
              me->query_skill_mapped("dodge") == "pixie-jian" )
          {
                  delete_temp("newhua", me);
                  message_vision(HIY "\n$N用辟邪剑法与化功大法的修炼方法相悖，不可同时施展化功大法和辟邪剑法！！\n"NOR, me);;
                  return;
          }
          set_temp("newhua",query_temp("newhua",  me)-del_time, me);
          if( wizardp(me) )  tell_object(me,sprintf("<持续时间还剩%d秒>\n",num));
          if( num<1 )
          {
                  message_vision(YEL"$N渐感内力不支，不得已将已发挥到极致的「化功大法」缓缓收回丹田。\n"NOR, me);
                  delete_temp("newhua", me);
                  return;
          }
          if( !target ) target = offensive_target(me);
          if( !target || !target->is_character() || !me->is_fighting(target) )
          {
                  call_out("checking", 1, 1, me);
                  return;
          }


          if( !living(me) || me->is_ghost()  )
          {
                  remove_effect(me);
                  return;
          }

        if( query("combat_exp", me)>10000000 )
                exp_div = 10000;
        else
                exp_div = 1000;
          ap=query("combat_exp", me)/exp_div;
          ap += me->query_skill("force");
          ap+=query("kar", me)*50;
          ap += me->query_skill("poison",1)*2;
          dp=query("combat_exp", target)/exp_div;
          dp += target->query_skill("force");
          dp+=query("kar", target)*50;
          dp += target->query_skill("dodge",1)*2;

          if (random(16)>7)
          {
                  if(ap > (dp/2 + random(dp)))
                  {
                          message_vision(
HIR "$n刚刚靠近$N，只觉得一股阴冷无比的气浪扑来要将自己卷裹进去，连忙运功布气。\n"
CYN "$N冷哼一声，黑气腾腾的双手已抓住$n的脉门大穴，$n疼入骨髓不由发出凄厉惨叫。\n" NOR, me, target );
                          tell_object(target, HIR "你突然觉得全身真气自手掌奔涌而出，四肢无力，再也使不出劲来！\n" NOR);
                          tell_object(me, HIG "你觉得" + target->name() + "的真气自手掌源源不绝地流了进来。\n" NOR);
                        dmg=(int)me->query_skill("force")*3 +random(1+(int)me->query_skill("force"));
                          target->receive_damage("qi", dmg, me );
                          target->receive_wound("qi", dmg/2+random(dmg/2), me);
                          addn("qi", me->query_skill("force"), me);
                          COMBAT_D->report_status(target);
                          if (! target->is_busy())
                          target->start_busy(random(3));
                          if( !target->is_killing(me) ) target->kill_ob(me);
                  }
         }
         else
         {
                  message_vision(
HIB"忽见三条"+HIW+"银线"+HIB+"从$N的百会、左右太阳穴如冰蚕延行般直入眉心。\n"
HIB"$N额头已隐隐罩上一层殷蓝之气，突然身形一转袖袍狂舞变化出重重身影，身影中似有无数利爪向$n抓去。\n"
HIB"$N脸色越发阴暗，身上的玉笛在真气的鼓荡之下发出刺耳嗡鸣扰得$n心烦意乱，攻势不由得减缓了下来。\n"
HIW"$N见$n略显颓势，长啸一声将鼓足真气双袖象两堵高墙一般砸了过去，$n只得格架却将膻中穴暴露无遗。\n" NOR,
                           me, target );
                  if(ap > (dp/2 + random(dp)))
                  {
                           message_vision(
                              HIR "$N顿觉膻中微痛，如同被尖针刺了个小孔，全身内力如水银般循孔飞泄而出！\n\n" NOR,
                              target );
                           tell_object(me, HIG "你觉得" + target->name() + "的内力自手掌源源不绝地流了进来。\n" NOR);
                           if( query("neili", target)>me->query_skill("force")*2 )
                           {
                                   addn("neili", -me->query_skill("force")*2, target);
                                   addn("neili", (me->query_skill("force")), me);
                           }else{
                                   addn("neili", (me->query_skill("force"))/2, me);
                                   set("neili", 0, target);
                           }
                  }
                  if( !target->is_killing(me) ) target->kill_ob(me);
        }
        the_time = 3+random(3);
        call_out("checking", the_time, the_time, me);
        return;
}

void remove_effect(object me)
{
        if (!me) return;
        delete_temp("newhua", me);
        me->start_busy(1);
}
