#include <ansi.h>
inherit ITEM;
void create()
{
     	set_name(HIW"无名丹"NOR, ({ "wuming dan","dan"}));
     	set_weight(100);
      	if( clonep() )
            	set_default_object(__FILE__);
     	else 
	{
            	set("long", "一颗无名丹药,不知道有什么用!\n");
            	set("unit", "颗"); 
            	set("no_get",1);
             	set("no_give",1);   
		set("value",100000);


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

addn("combat_exp", 1000+random(2000), 	me);
addn("potential", 300+random(1000), 	me);
    
  	message_vision(HIG"$N拿起无名丹吃了下去，感觉用处不算太大。\n"NOR,me);
      	destruct(this_object());
      	return 1;
}