// ITEM Made by player(小球球:ovo) /data/item/o/ovo-xuey.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Apr  5 11:59:13 2019
#include <ansi.h>
#include <armor.h>

inherit FINGER;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;32m学之指套[2;37;0m", ({ "xuey" }));
	set_weight(3500);
	set("item_make", 1);
	set("unit", "套");
	set("long", "这是由[1;37m寰宇天晶[2;37;0m炼制而成的一套指套。
");
	set("makeinfo", "[1;31m
小球球(ovo)[1;31m 出品
[2;37;0m");
	set("value", 4100000);
	set("point", 447);
	set("max_consistence", 100);
	set("material", "tian jing");
	set("material_file", "/clone/goods/tianjing");
	set("quality_level", 3);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);
	set("armor_prop/study_times", 5);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
