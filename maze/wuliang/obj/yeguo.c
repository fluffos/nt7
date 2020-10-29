// yeguo.c

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("野果", ({"ye guo", "guo"}));
	set_weight(80);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "个");
		set("value", 50);
		set("food_remaining", 3);
		set("food_supply", 20);
	}
}