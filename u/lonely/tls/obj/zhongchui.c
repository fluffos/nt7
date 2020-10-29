
#include <weapon.h>

inherit HAMMER;

void create()
{
	set_name("钟槌", ({ "zhong chui","chui" }) );
	set_weight(3000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long", "这是一把沉甸甸的钟槌，竟然是用铁木制成，坚硬异常。\n");
		set("value", 3);
		set("material", "iron");
		set("wield_msg", "$N拿出一把$n，握在手中。\n");
		set("unwield_msg", "$N放下手中的$n。\n");
	}

	init_hammer(15);
	setup();
}
