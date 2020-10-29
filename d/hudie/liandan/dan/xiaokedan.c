#include <ansi.h>
inherit ITEM;
void create()
{
     	set_name(HIR"消渴止饿丹"NOR, ({ "xiaoke dan","dan"}));
      	set_weight(100);
      	if( clonep() )
            	set_default_object(__FILE__);
       else 
	{       
         	set("unit", "颗"); 
             	set("no_get",1);
            	set("no_give",1);
      	}
    	setup();
}
void init()
{
    	if (environment()==this_player())
        	add_action("do_eat", "eat");
}
int do_eat(string arg)
{
  	object me = this_player();
    
  	if(!id(arg)) return 0;
  	if(me->is_busy()) return notify_fail("你上一个动作还没有完成。\n");
    
   addn("food", 5*me->max_food_capacity(), me);
   addn("water", 5*me->max_food_capacity(), me);

 	message_vision(HIR"$N拿起消渴止饿丹吃了下去，感觉精神一振，饥渴的感觉不复存在。\n"NOR,me);
       destruct(this_object());
       return 1;
}