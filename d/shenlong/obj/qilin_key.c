inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIR "麒麟钥匙" NOR, ({"qilin key", "key", "qilin"}));
	/*if (clonep())
		set_default_object(__FILE__);
	else*/ {
        	set("unit", "把");
		set("long", HIR "这是一把通体火红的钥匙，测试期间可代替斩妖勋章来打开火麒麟洞的封印。\n");
		set("value", 1);
	}
        setup();
}