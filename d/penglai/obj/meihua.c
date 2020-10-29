#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIY "梅花" NOR, ({ "penglai meihua" }) );
	set_weight(100);
	/*if( clonep() )
		set_default_object(__FILE__);
	else*/ {
		set("unit", "朵");
		set("value", 1);
		set("long", HIY "这是一朵梅花，花瓣清香令人陶醉。\n" NOR);
	}

	setup();
}

int query_autoload()
{
	return 1;
}