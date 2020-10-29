
inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name("大碗", ({"da wan", "wan", "bowl"}));
	set_weight(700);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一个用来装水的大碗。\n");
		set("unit", "个");
		set("value", 100);
		set("max_liquid", 15);
	}

	// because a container can contain different liquid
	// we set it to contain wine at the beginning
	set("liquid", ([
		"type": "water",
		"name": "水",
		"remaining": 15,
		"drunk_apply": 3,
	]));
}
