// jiexue.c
// 冲开封闭的穴道

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
         int force;
         object ob;

         if (me->is_busy() || me->is_fighting())
                 return notify_fail("等你忙完再说吧！\n");

         force = me->query_skill("force");

         if (1)
         {
                if (! me->query_temp("fengxue"))
                      return notify_fail("你穴道并没有封闭啊。\n");
          
                if (force < 300)
                      return notify_fail("你内功修为不足，无法将封闭的穴道冲开。\n");

                if (me->query("max_neili") < 2000)
                      return notify_fail("你内力修为不足，无法将封闭的穴道冲开。\n");

                message_vision(HIW "$N" HIW "暗运内功，一股真气流至全身各处。\n" NOR, me);

                write(HIG "你周身被封闭的穴道已被冲开。\n" NOR);

                me->delete_temp("fengxue");
                me->set_temp("last_fengxue", time());
                me->start_busy(2);

                return 1;
         }    
}

int help(object me)
{
  write(@HELP
指令格式 : chongxue

该指令可以将被封闭的穴道冲开。
HELP
);
    return 1;
}
 
