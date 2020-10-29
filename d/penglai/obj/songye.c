#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(YEL + GRN "松叶" NOR, ({ "penglai songye" }) );
	set_weight(100);
	/*if( clonep() )
		set_default_object(__FILE__);
	else*/ {
		set("unit", "片");
		set("value", 1);
		set("long", YEL + GRN "这是一片从长松树上落下的松叶。\n" NOR);
	}

	setup();
}

int query_autoload()
{
	return 1;
}