// Code of ShenZhou
#include <ansi.h>

inherit ITEM;
int cure_ob(string);
void create()
{
   set_name("雄黄丸", ({"xionghuang wan", "xionghuang", "wan"}));
   /*if (clonep())
      set_default_object(__FILE__);
   else*/ {
      set("unit", "颗");
      set("value", 4000);
                set("no_sell", 1);
      set("long", "这是一颗丐帮特制能解百毒的雄黄丸，尤其对蛇嗤虫咬之伤更见神效。\n");
      set("medicine", 1);
   }
   setup();
}

int cure_ob(object me)
{
   message_vision("$N吃下一颗" + name() + "。\n", me);

   if ( !me->query_condition("xx_poison") && !me->query_condition("snake_poison")
   && !me->query_condition("insect_poison") ) {
        me->apply_condition("snake_poison", 10);
        me->apply_condition("insect_poison", 10);
        me->query_condition("xx_poison", 5);
        tell_object(me, HIR "你没伤胡乱服食丹药，反有大害！\n\n" NOR);
        destruct(this_object());
          return 1;
   }        

   if ( (int)me->query_condition("snake_poison") ) {
      me->apply_condition("snake_poison", (int)me->query_condition("snake_poison") - 10);
      if ( (int)me->query_condition("snake_poison") < 0 ) me->apply_condition("snake_poison", 0);
      set_temp("xhwan", 1, me);
   }

   if ( (int)me->query_condition("insect_poison") ) {
      me->apply_condition("insect_poison", (int)me->query_condition("insect_poison") - 10);
      if ( (int)me->query_condition("insect_poison") < 0 ) me->apply_condition("insect_poison", 0);
      set_temp("xhwan", 1, me);
   }

   if( me->query_condition("xx_poison")>100 && !query_temp("xhwan", me)){
        return notify_fail("你中的抽髓掌毒太深，现在服此药没什么效用。\n");
   }
   else {
      me->apply_condition("xx_poison", (int)me->query_condition("xx_poison") - 5);
      if ( (int)me->query_condition("xx_poison") < 0 ) me->apply_condition("xx_poison", 0);
      set_temp("xhwan", 1, me);
   }

   if( me->query_condition("sl_poison")>100 && !query_temp("xhwan", me)){
        return notify_fail("你中的化骨绵掌毒太深，现在服此药没什么效用。\n");
   }
   else {
      me->apply_condition("sl_poison", (int)me->query_condition("sl_poison") - 5);
      if ( (int)me->query_condition("sl_poison") < 0 ) me->apply_condition("sl_poison", 0);
   }

   message_vision(YEL "$N只觉毒伤大为好转，可见此丹灵效。\n\n" NOR, me);
   
   delete_temp("xhwan", me);
   destruct(this_object());
   return 1;
}