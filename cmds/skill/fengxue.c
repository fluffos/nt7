// fengxue.c
// 封闭穴道防止毒气扩散和发作

#include <ansi.h>

inherit F_CLEAN_UP;

void end_fengxue(object me)
{
         if (me->query_temp("fengxue"))
         {
               write(HIG "你长舒一口气，周身被封闭的穴道已自动解开。\n");
 
               me->delete_temp("fengxue");

               me->set_temp("last_fengxue", time());        
         }

         return;         
}

// 还要添加set fengxue 1

int main(object me, string arg)
{
         int force;
         object ob;

         if (me->is_busy() || me->is_fighting())
                 return notify_fail("等你忙完再说吧！\n");


         if (time() - me->query_temp("last_fengxue") < 60)
                 return notify_fail("你的穴道刚冲开，不能继续封穴了。\n");

         force = me->query_skill("force");
/*
         if (me->query_skill("jingluo-xue", 1) < 100)
                  return notify_fail("你对经络学了解不够，无法封穴。\n");
*/
         if (! arg)
         {
                if (me->query_temp("fengxue"))
                      return notify_fail("你已经将周身要穴封闭。\n");                
          
                if (force < 300)
                      return notify_fail("你内功修为不足，无法将自己穴道封闭。\n");

                if (me->query("max_neili") < 2000)
                      return notify_fail("你内力修为不足，无法将自己穴道封闭。\n");

                message_vision(HIW "$N" HIW "暗运内息，右手食指猛地点向周身各"
                               "处，将要穴封闭。\n" NOR, me);

                me->set_temp("fengxue", 1);

                me->start_busy(2);

                me->start_call_out((: call_other, __FILE__,
                               "end_fengxue", me:), force / 5);

                return 1;                
         }    
         
         if( !objectp(ob = present(arg, environment(me))) )
		 return notify_fail("这里没有 " + arg + "。\n");
         
         if (! playerp(ob))
                 return notify_fail("你只能帮助玩家封穴。\n");

         if (! ob->query("env/fengxue") || ob->query_temp("fengxue"))
                 return notify_fail("对方现在不需要你帮助封穴。\n");

         if (force < 400)
                 return notify_fail("你内功修为不足，无法帮助其他玩家封穴。\n");

         if (me->query("neili") < 300)
                 return notify_fail("你内力不足，无法帮助其他玩家封穴。\n");

         if (me->query("max_neili") < 3000)
                 return notify_fail("你内力修为不足，无法帮助其他玩家封穴。\n");

         message_vision(HIY "$N" HIY "将内力运于指间，猛地点向$n" HIY "周"
                        "身各处，将其要穴封闭。\n" NOR, me, ob);

         ob->set_temp("fengxue", 1);

         ob->start_busy(2);
         me->start_busy(2);
         me->add("neili", -220);

         me->start_call_out((: call_other, __FILE__,
                           "end_fengxue", ob:), force / 5);
         return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : fengxue [玩家ID]

该指令可以在中毒时暂时将穴道封闭，以免毒性发作。
当穴道冲开后一分钟内不能再继续封穴。

HELP
);
    return 1;
}
 
