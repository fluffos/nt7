#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(YEL + GRN "竹叶" NOR, ({ "penglai zhuye" }) );
	set_weight(100);
	/*if( clonep() )
		set_default_object(__FILE__);
	else*/ {
		set("unit", "片");
		set("value", 1);
		set("long", YEL + GRN "这是一片竹叶，还带着仙气。\n" NOR);
	}

	setup();
}

int query_autoload()
{
	return 1;
}