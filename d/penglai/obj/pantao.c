#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIM "蓬莱蟠桃" NOR, ({ "penglai pantao" }) );
	set_weight(100);
	/*if( clonep() )
		set_default_object(__FILE__);
	else*/ {
		set("unit", "个");
		set("value", 1);
		set("long", HIM "这是一个蓬莱蟠桃，据说每二百年才结果。\n" NOR);
	}

	setup();
}

int query_autoload()
{
	return 1;
}