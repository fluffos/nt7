#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIM "蝴蝶标本" NOR, ({ "hudie biaoben" }) );
	set_weight(100);
	/*if( clonep() )
		set_default_object(__FILE__);
	else*/ {
		set("unit", "个");
		set("value", 1);
		set("long", HIM "这是蝶仙用死去的蝴蝶做成的标本。\n" NOR);
	}

	setup();
}

int query_autoload()
{
	return 1;
}