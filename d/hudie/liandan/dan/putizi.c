#include <ansi.h>
inherit ITEM;
void create()
{
      	set_name(YEL"菩提子"NOR, ({ "puti zi","zi"}));
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
  	int maxneili,neili;
    	neili=query("neili", me);
    	maxneili=query("max_neili", me);
    
  	if(!id(arg)) return 0;
  	if(me->is_busy()) return notify_fail("你上一个动作还没有完成。\n");
        if( time()-query("eat_drug/putizi", me)<1800 )
                return notify_fail("你觉得现在内息未定，经脉隐隐还能感到真气冲荡，不敢贸然服食。\n");

        addn("max_neili", 10+random(15), me);message_vision(HIG"$N拿起菩提子吃了下去,感觉丹田传来一阵阵热意,内力修为好象有所增加!!!!!\n"NOR,me);
      set("eat_drug/putizi", time(), me);
      	destruct(this_object());
      	return 1;
}