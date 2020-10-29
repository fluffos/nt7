#include <ansi.h>
inherit ITEM;
void setup()
{}
void init()
{
	add_action("do_eat", "eat");
}
void create()
{
	set_name("雪露丸", ({"xuelu wan", "wan", }));   
	set("no_drop",1);
	set("no_get",1);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "颗");
		set("long", "这是一颗晶莹半透明的药丸，浅绿色带有一股清香，此药是天龙寺秘传以天山雪莲与碧玉草合成，提高体力，灵效无比。\n");
		set("value", 10000);     
		set("no_drop",1);
	set("no_get",1);
		
	}

	set("tialongsi",1);
	setup();
}

int do_eat(string arg)
{
	object me = this_player();

	if (!id(arg))
	return notify_fail("你要吃什么？\n");

	if ( me->query_skill_mapped("force") != "qiantian-yiyang" )
      {
       if ( me->query_skill_mapped("force") != "kurong-changong" )
	{
	/*
		if (me->add("max_jingli", -20) < 0)
			me->set("max_jingli", 0);
		if (me->add("eff_jingli", -20) < 0)
			me->set("eff_jingli", 0);
		message_vision(HIR "$N吃下一颗雪露丸，只觉得肝肠寸断，原来所练内功不符，反而大损体力！\n" NOR, me);
		me->unconcious();
		destruct(this_object());
	*/
		write("所练内功不符，这药你还是不要吃的好！\n");
		return 1;
	}
      } 

	if ( (int)me->query_condition("bonze_drug" ) > 0 )
	{
		if (me->add("max_jingli", -1) < 0)
			me->set("max_jingli", 0);
		if (me->add("eff_jingli", -1) < 0)
			me->set("eff_jingli", 0);
		message_vision(HIR "$N吃下一颗雪露丸，只觉得头重脚轻，摇摇欲倒，原来服食太急太多，药效适得其反！\n" NOR, me);
	}
	else
	{
		me->add("max_jingli", 1);
		me->add("eff_jingli", 1);
		message_vision(HIY "$N吃下一颗雪露丸，只觉得体力顿然提高，全身似有无穷的精力！\n" NOR, me);
		me->apply_condition("bonze_drug", 25);
	}
	
	destruct(this_object());
	return 1;
}
