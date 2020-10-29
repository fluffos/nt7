// ITEM Made by player(涂鸦人生:mlove) /data/item/m/mlove-mlk.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan  9 22:51:15 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("研究套[2;37;0m", ({ "mlk" }));
	set_weight(4000);
	set("item_make", 1);
	set("unit", "双");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一双护手。
");
	set("makeinfo", "[1;31m
涂鸦人生(mlove)[1;31m 出品
[2;37;0m");
	set("value", 34980000);
	set("point", 1744);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 4);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);
	set("armor_prop/avoid_dodge", 1.200000);
	set("armor_prop/double_damage", 1.500000);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
