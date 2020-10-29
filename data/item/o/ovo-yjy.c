// ITEM Made by player(小球球:ovo) /data/item/o/ovo-yjy.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Apr  9 22:22:12 2019
#include <ansi.h>
#include <armor.h>

inherit FINGER;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;34m烟酒指套[2;37;0m", ({ "yjy" }));
	set_weight(350);
	set("item_make", 1);
	set("unit", "套");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一套指套。
");
	set("makeinfo", "[1;31m
小球球(ovo)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 703);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 5);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);
	set("armor_prop/add_poison", 2);
	set("armor_prop/research_effect", 2);
	set("armor_prop/attack", 20);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
