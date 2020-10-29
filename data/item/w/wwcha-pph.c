// ITEM Made by player(大波龙:wwcha) /data/item/w/wwcha-pph.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Jan 19 18:27:02 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;36m插死你[2;37;0m", ({ "pph" }));
	set_weight(20000);
	set("item_make", 1);
	set("unit", "件");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一件战衣。
");
	set("makeinfo", "[1;31m
大波龙(wwcha)[1;31m 出品
[2;37;0m");
	set("value", 35380000);
	set("point", 1764);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 6);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/practice_effect", 3);
	set("armor_prop/research_effect", 6);
	set("armor_prop/avoid_busy", 2.500000);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
