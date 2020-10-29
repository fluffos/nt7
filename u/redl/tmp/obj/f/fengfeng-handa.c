// ITEM Made by player(风风:fengfeng) /data/item/f/fengfeng-handa.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Sep 22 18:35:30 2014
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;36m[46m青梅掌[2;37;0m", ({ "handa" }));
	set_weight(450);
	set("item_make", 1);
	set("unit", "双");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一双铁掌。
");
	set("makeinfo", "[1;31m
风风(fengfeng)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 1500);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 6);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);
	set("armor_prop/fatal_blow", 2.000000);
	set("armor_prop/add_blind", 2.000000);
	set("armor_prop/add_weak", 2.500000);
	set("armor_prop/add_freeze", 2.500000);
	set("armor_prop/add_forget", 2.500000);
	set("armor_prop/da_power", 2.000000);
	set("armor_prop/ap_power", 2.000000);
	set("armor_prop/add_damage", 2.500000);
	set("armor_prop/add_busy", 2.500000);
	set("armor_prop/double_damage", 2.000000);

	setup();
}

string long() { return short() + query("makeinfo") + query("long") + item_long(); }
