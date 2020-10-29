// ITEM Made by player(糙汉:run) /data/item/r/run-boots.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Feb  1 16:59:11 2019
#include <ansi.h>
#include <armor.h>

inherit BOOTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("靴子[2;37;0m", ({ "boots" }));
	set_weight(600);
	set("item_make", 1);
	set("unit", "双");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一双靴子。
靴子一双[2;37;0m
");
	set("makeinfo", "[1;31m
糙汉(run)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 600);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 6);
	set("wear_msg", "一双靴子横空出世[2;37;0m\n");
	set("remove_msg", "一双靴子不见了[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/counter_damage", 2.500000);
	set("armor_prop/avoid_poison", 1.500000);
	set("armor_prop/avoid_weak", 2.500000);
	set("armor_prop/research_effect", 3);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
