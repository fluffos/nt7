// ITEM Made by player(小球球:ovo) /data/item/o/ovo-nlh.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jun 16 00:52:03 2019
#include <ansi.h>
#include <armor.h>

inherit BOOTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;35m内内靴子[2;37;0m", ({ "nlh" }));
	set_weight(6000);
	set("item_make", 1);
	set("unit", "双");
	set("long", "这是由[1;37m寰宇天晶[2;37;0m炼制而成的一双靴子。
");
	set("makeinfo", "[1;31m
小球球(ovo)[1;31m 出品
[2;37;0m");
	set("value", 4100000);
	set("point", 320);
	set("max_consistence", 100);
	set("material", "tian jing");
	set("material_file", "/clone/goods/tianjing");
	set("quality_level", 5);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/derive_effect", 3);
	set("armor_prop/reduce_busy", 2.500000);
	set("armor_prop/max_neili", 10000);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
