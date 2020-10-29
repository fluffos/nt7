#include <ansi.h>
inherit ITEM;
void create()
{
    	set_name(HIG"疾风骤雨丹"NOR, ({ "jifengzhouyu dan","dan"}));
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

  	if (!me->is_fighting())
		return notify_fail("你现在没有在战斗中，吃了也没什么用。\n");

	me->start_busy(0);
  	message_vision(HIG"$N吞下一颗疾风骤雨丹，身如疾风，脱离了忙乱状态，转身一招又攻了过来！\n"NOR,me);
      	destruct(this_object());
      	return 1;
}