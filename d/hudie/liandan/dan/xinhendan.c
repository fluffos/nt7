#include <ansi.h>
inherit ITEM;
void create()
{
     	set_name(HIG"心狠手辣丹"NOR, ({ "xinhen dan","dan"}));
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
    
addn("shen", -50000, 	me);
 	message_vision(HIB"$N拿起心狠手辣丹吃了下去，感觉丹田传来一阵阵寒意，双眼冒出狠辣杀气！！！\n"NOR,me);
       destruct(this_object());
       return 1;
}