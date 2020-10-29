// dan.c

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
	set_name("毒丹", ({"du dan", "du", "dan"}));
	set_weight(150);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "颗");
		set("long", "这是一颗黑色的丹丸，好象有毒。\n");
		set("value", 100000);
		set("no_get", 1);
		set("no_drop", 1);
	}
	setup();
}

int do_eat(string arg)
{
	object me = this_player();

	if (!id(arg))
		return notify_fail("你要吃什么？\n");

	if ( me->query_skill_mapped("force") == "qiantian-yiyang" )
		return notify_fail("你现在所用内功不对，吃了反而会大损元气。\n");
       
	if ( (int)me->query_condition("bonze_drug" ) > 0 )
		return notify_fail("你刚吃过灵药，现在不能吃毒丹! \n");

	if ( me->query_skill_mapped("force") == "kurong-changong"){
		me->set("eff_qi", me->query("max_qi"));
		me->set("food", me->max_food_capacity());
		me->set("water", me->max_water_capacity());
		message_vision(HIG "$N吃下一颗毒丹，反而觉得精气一振，似乎略有增涨。\n" NOR,me);
		destruct(this_object());
		return 1;
	}
	else {
		me->add("qi", -200);
		me->add("jing", -100);
                me->set("eff_qi", me->query("max_qi"));
		message_vision(HIR "$N吃下一颗毒丹，只觉得肝肠寸断。\n" NOR, me);
		me->unconcious();
		destruct(this_object());
		return 1;
	}
	me->apply_condition("bonze_drug", 60);
	destruct(this_object());
	return 1;
}
