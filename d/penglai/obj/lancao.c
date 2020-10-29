#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIG "兰草" NOR, ({ "penglai lancao" }) );
	set_weight(100);
	/*if( clonep() )
		set_default_object(__FILE__);
	else*/ {
		set("unit", "棵");
		set("value", 1);
		set("long", HIY "这是一棵兰草，形状很奇特，似乎在人间未曾见过。\n" NOR);
	}

	setup();
}

int query_autoload()
{
	return 1;
}