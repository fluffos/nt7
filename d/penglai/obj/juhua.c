#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIY "菊花" NOR, ({ "penglai juhua" }) );
	set_weight(100);
	/*if( clonep() )
		set_default_object(__FILE__);
	else*/ {
		set("unit", "朵");
		set("value", 1);
		set("long", HIY "这是一朵菊花，花瓣呈现出各种不同的颜色，据说只有蓬莱仙岛才有。\n" NOR);
	}

	setup();
}

int query_autoload()
{
	return 1;
}