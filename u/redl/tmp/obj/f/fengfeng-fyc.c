// ITEM Made by player(风风:fengfeng) /data/item/f/fengfeng-fyc.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Oct  4 11:25:52 2014
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("[41;1m[1;33m福源护甲[2;37;0m", ({ "fyc" }));
	set_weight(1050);
	set("item_make", 1);
	set("unit", "张");
	set("long", "这是由[1;37m冰蚕丝[2;37;0m炼制而成的一张护甲。
");
	set("makeinfo", "[1;31m
风风(fengfeng)[1;31m 出品
[2;37;0m");
	set("value", 2100000);
	set("point", 400);
	set("max_consistence", 100);
	set("material", "silk");
	set("material_file", "/d/item/obj/tiancs");
	set("quality_level", 5);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/jing_recover", 40);
	set("armor_prop/kar", 3);
	set("armor_prop/research_effect", 3);

	setup();
}

string long() { return short() + query("makeinfo") + query("long") + item_long(); }
