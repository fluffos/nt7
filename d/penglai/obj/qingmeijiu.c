#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIY "青梅酒" NOR, ({ "penglai qingmeijiu" }) );
	set_weight(100);
	/*if( clonep() )
		set_default_object(__FILE__);
	else*/ {
		set("unit", "瓶");
		set("value", 1);
		set("long", HIY "这是一瓶精心酿制的青梅酒，虽然装在瓶中，却依然无法掩盖其香气。\n" NOR);
	}

	setup();
}

int query_autoload()
{
	return 1;
}