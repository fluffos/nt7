// ITEM Made by player(风风:fengfeng) /data/item/f/fengfeng-fyi.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Oct  4 11:25:00 2014
#include <ansi.h>
#include <armor.h>

inherit SURCOAT;
inherit F_ITEMMAKE;

void create()
{
	set_name("[41;1m[1;33m福源披风[2;37;0m", ({ "fyi" }));
	set_weight(10000);
	set("item_make", 1);
	set("unit", "件");
	set("long", "这是由[1;37m寰宇天晶[2;37;0m炼制而成的一件披风。
");
	set("makeinfo", "[1;31m
风风(fengfeng)[1;31m 出品
[2;37;0m");
	set("value", 4100000);
	set("point", 500);
	set("max_consistence", 100);
	set("material", "tian jing");
	set("material_file", "/clone/goods/tianjing");
	set("quality_level", 5);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/kar", 6);
	set("armor_prop/max_jing", 2200);

	setup();
}

string long() { return short() + query("makeinfo") + query("long") + item_long(); }
