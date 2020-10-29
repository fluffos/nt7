// ITEM Made by player(泡泡:step) /data/item/s/step-chuc.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Apr 15 17:40:27 2019
#include <ansi.h>
#include <armor.h>

inherit BOOTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("云靴[2;37;0m", ({ "chuc" }));
	set_weight(6000);
	set("item_make", 1);
	set("unit", "双");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一双靴子。
");
	set("makeinfo", "[1;31m
泡泡(step)[1;31m 出品
[2;37;0m");
	set("value", 35860000);
	set("point", 715);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 5);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/avoid_blind", 3.000000);
	set("armor_prop/max_jing", 2200);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
