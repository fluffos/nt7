// ITEM Made by player(小球球:ovo) /data/item/o/ovo-jli.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Jun 15 18:44:48 2019
#include <ansi.h>
#include <armor.h>

inherit SURCOAT;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[33m精力披风[2;37;0m", ({ "jli" }));
	set_weight(1000);
	set("item_make", 1);
	set("unit", "件");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一件披风。
");
	set("makeinfo", "[1;31m
小球球(ovo)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 750);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 5);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/max_jingli", 4500);
	set("armor_prop/reduce_poison", 1.500000);
	set("armor_prop/avoid_weak", 2.500000);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
