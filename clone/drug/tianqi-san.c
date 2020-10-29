// Code of HUAXIA
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "田七鲨胆散" NOR, ({"tianqi san", "san"}));
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "包");
                set("long", "：这是一包田七鲨胆散，可解化尸粉毒。\n");
                set("value", 10000);
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
   if (!me->query_condition("hsf_poison"))
   {
      tell_object(me, "你又没中化尸粉毒，乱吃药干嘛？\n");
      return 1;
   }

   message_vision("$N吃下一包" + name() + "。\n", me);
   tell_object(me, "你觉得嘴里非常的苦。\n");

   if ((int)me->query_condition("hsf_poison") < 100) {
      me->clear_condition("hsf_poison");
      tell_object(me, "你觉得伤口不再疼痛，化尸粉毒已经解除了。\n");
   } else if ((int)me->query_condition("hsf_poison") >= 100)
   {
      me->apply_condition("hsf_poison",(int)me->query_condition("hsf_poison")-90);
      tell_object(me, "你觉得好受了一点，不过化尸粉毒还没有完全消除。\n");
   }

   destruct(this_object());
   return 1;
}