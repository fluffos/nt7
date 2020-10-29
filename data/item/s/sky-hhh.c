// ITEM Made by player(渡天:sky) /data/item/s/sky-hhh.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jun 19 15:02:12 2019
#include <ansi.h>
#include <armor.h>

inherit SURCOAT;
inherit F_ITEMMAKE;

void create()
{
	set_name("[45;1m山河图[2;37;0m", ({ "hhh", "hhh" }));
	set_weight(10000);
	set("item_make", 1);
	set("unit", "件");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一件披风。
");
	set("makeinfo", "[1;31m
渡天(sky)[1;31m 出品
[2;37;0m");
	set("value", 35160000);
	set("point", 876);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 6);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/full_self", 2.500000);
	set("armor_prop/research_effect", 9);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
