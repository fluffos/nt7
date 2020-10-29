// ITEM Made by player(糙汉:run) /data/item/r/run-cloth.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Feb  1 13:26:55 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("战衣[2;37;0m", ({ "cloth" }));
	set_weight(20000);
	set("item_make", 1);
	set("unit", "件");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一件战衣。
这个衣服很好看[2;37;0m
");
	set("makeinfo", "[1;31m
糙汉(run)[1;31m 出品
[2;37;0m");
	set("value", 35500000);
	set("point", 1770);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 6);
	set("wear_msg", "衣服穿起来，漂亮极了[2;37;0m\n");
	set("remove_msg", "衣服收起来，光秃秃的[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/avoid_freeze", 0);
	set("armor_prop/counter_damage", 2.500000);
	set("armor_prop/practice_effect", 3);
	set("armor_prop/research_effect", 3);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
