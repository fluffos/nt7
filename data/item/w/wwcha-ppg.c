// ITEM Made by player(大波龙:wwcha) /data/item/w/wwcha-ppg.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Jan  7 10:48:38 2019
#include <ansi.h>
#include <armor.h>

inherit BOOTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;37m最[1;35m爱[1;31m你[2;37;0m", ({ "ppg" }));
	set_weight(6000);
	set("item_make", 1);
	set("unit", "双");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一双靴子。
");
	set("makeinfo", "[1;31m
大波龙(wwcha)[1;31m 出品
[2;37;0m");
	set("value", 35760000);
	set("point", 713);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 2);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
