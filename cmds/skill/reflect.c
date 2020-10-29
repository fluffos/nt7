// reflect.c
// 冥思指令获取少量经验和潜能
// 会员专用指令 Create by Rcwiz for HERO.CD

#include <ansi.h>
#define MEMBER_D     "/adm/daemons/memberd"

inherit F_CLEAN_UP;

void end_reflect(object me)
{
         mixed exp, pot;

         if( query_temp("reflect", me) )
         {
               message_vision(HIY "$N" HIY "冥思完毕，缓缓地睁开眼睛，似乎若有所悟！\n" NOR, me);
 
               delete_temp("reflect", me);

               exp=query("combat_exp", me);
               exp /= 100000;
               if (exp > 2000) exp = 2000;
               pot = exp / 5;

               exp = exp + random(exp / 2);
               pot = pot + random(pot / 2);
               if( query("jingmai/reflect", me) )
               {
                       exp+=exp*query("jingmai/reflect", me)/100;
                       pot+=pot*query("jingmai/reflect", me)/100;
               }

               addn("combat_exp", exp, me);
               addn("potential", pot, me);

               write(HIG "通过这次冥思，你获得了" HIC + chinese_number(exp) + HIG 
                     "点实战经验和" HIC + chinese_number(pot) + HIG "点潜能。\n");

         }

         if (! me->is_busy())me->start_busy(1);
         return;
}

int main(object me)
{
         object ob;


         if (me->is_busy() || me->is_fighting())
                 return notify_fail("等你忙完再说吧！\n");

         if( query_temp("reflect", me) )
                 return notify_fail("你正在冥思。\n");

         if (! wizardp(me) && ! MEMBER_D->is_valid_member(query("id", me)))
                 return 0;

         if( !query("doing", me) )
                 return notify_fail("只有计划时才能冥思。\n");

         if( query("combat_exp", me)<1000000 )
                  return notify_fail("你实战经验，无法冥思。\n");

         if (me->query_skill("martial-cognize", 1) < 160)
                  return notify_fail("你武学修养不足，无法冥思。\n");
 

         set_temp("reflect", 1, me);

         me->start_busy(30);

         me->start_call_out((: call_other, __FILE__,
                             "end_reflect", me:), 28 + random(6));

         message_vision(HIY "$N" HIY "盘膝而坐，闭目冥思 ……\n" NOR, me);

         return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : reflect

该指令可以在计划时使用以提高少量经验和潜能。
该指令只限会员使用。

HELP
);
    return 1;
}
 
