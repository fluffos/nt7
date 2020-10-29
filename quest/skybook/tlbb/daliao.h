#include <ansi.h>

int valid_leave(object me, string dir)
{
  if(present("liao bing",environment(me)))  return notify_fail("辽兵一把将你拦住：哪里跑！\n" );
  return ::valid_leave(me, dir);
}
void init()
{
  object me,obj;
  me = this_player();
   if(me->query_condition("killer"))
  {
   message_vision(HIC"\n突然$N似乎气血有些不顺，跟着一个趔趄倒了下去。\n"NOR,me); 
   tell_object(me,HIR"你突然感到一股力量吸引着你，瞬间你失去知觉。\n"NOR);
   tell_room(environment(me),HIR"\n只见，地上突然出现一个裂洞，"+ me->name()+ "一头扎了下去，瞬间消失。\n"NOR, ({ }));
   me->move(__DIR__"shanlu1"); 
   tell_room(environment(me), HIR"\n半空中，似乎一个人掉了下来，你定眼一看竟然是"+ me->name()+ "。\n"NOR, ({}));
   me->unconcious();
   return;
  }
  if(!me->query("quest/天龙八部/大辽救援篇/start")) return;
   if(me->query("quest/天龙八部/大辽救援篇/over")) return; 
  if(!me->query_temp("quest/天龙八部/大辽救援篇/godaliao")) return; 
 
  obj=new(__DIR__"npc/liaobing");
  obj->set("teamleader",1);
  obj->set("fight_id",me->query("id"));
  obj->move(environment(me)); 
}
