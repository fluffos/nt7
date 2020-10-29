// ITEM Made by player(风四郎:alxpang) /data/item/a/alxpang-irone.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Jan 26 10:19:20 2019
#include <ansi.h>
#include <armor.h>

inherit WRISTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("青钢腕[2;37;0m", ({ "irone" }));
	set_weight(500);
	set("item_make", 1);
	set("unit", "对");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一对护腕。
");
	set("makeinfo", "[1;31m
风四郎(alxpang)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 75);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 2);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }