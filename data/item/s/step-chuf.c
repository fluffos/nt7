// ITEM Made by player(泡泡:step) /data/item/s/step-chuf.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Apr 16 09:34:51 2019
#include <ansi.h>
#include <armor.h>

inherit SURCOAT;
inherit F_ITEMMAKE;

void create()
{
	set_name("云风[2;37;0m", ({ "chuf" }));
	set_weight(10000);
	set("item_make", 1);
	set("unit", "件");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一件披风。
");
	set("makeinfo", "[1;31m
泡泡(step)[1;31m 出品
[2;37;0m");
	set("value", 34220000);
	set("point", 853);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 5);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/study_times", 15);
	set("armor_prop/reduce_busy", 2.500000);
	set("armor_prop/study_effect", 3);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
