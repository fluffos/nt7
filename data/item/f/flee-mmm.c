// ITEM Made by player(桃枝妖妖:flee) /data/item/f/flee-mmm.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Feb 15 18:58:57 2019
#include <ansi.h>
#include <armor.h>

inherit BOOTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;32m人字拖[2;37;0m", ({ "mmm" }));
	set_weight(6000);
	set("item_make", 1);
	set("unit", "双");
	set("long", "这是由[1;37m寰宇天晶[2;37;0m炼制而成的一双靴子。
");
	set("makeinfo", "[1;31m
桃枝妖妖(flee)[1;31m 出品
[2;37;0m");
	set("value", 4100000);
	set("point", 400);
	set("max_consistence", 100);
	set("material", "tian jing");
	set("material_file", "/clone/goods/tianjing");
	set("quality_level", 3);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/max_neili", 10000);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
