#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIC "青梅" NOR, ({ "penglai qingmei" }) );
	set_weight(100);
	/*if( clonep() )
		set_default_object(__FILE__);
	else*/ {
		set("unit", "颗");
		set("value", 1);
		set("long", HIC "从长生梅林中采集而来的青梅。\n" NOR);
	}

	setup();
}

int query_autoload()
{
	return 1;
}