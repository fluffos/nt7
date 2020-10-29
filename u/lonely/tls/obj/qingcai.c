
inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("青菜", ({"qing cai", "cai"}));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一盆炒好的青菜。\n");
		set("unit", "盆");
		set("value", 150);
		set("food_remaining", 3);
		set("food_supply", 60);
	}
}
