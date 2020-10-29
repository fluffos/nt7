#include <ansi.h>
inherit ITEM;
#include <ansi.h>
void create()
{
     	set_name(HIY"龙犀百草丹"NOR, ({ "longxi dan","dan"}));
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
    	if (!id(arg))  return notify_fail("你要吃什么？\n");
	this_player()->clear_condition();
 
   	message_vision(HIC "$N吞下龙犀百草丹，一股热力从丹田升起，渐渐的渗入全身血脉，毒素的作用逐渐消失了。\n" NOR,this_player() );
    	destruct(this_object());
    	return 1;
}