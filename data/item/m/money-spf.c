// ITEM Made by player(财迷:money) /data/item/m/money-spf.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan 16 11:43:47 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("[43;1m纯金衬衣[2;37;0m", ({ "spf" }));
	set_weight(20000);
	set("item_make", 1);
	set("unit", "件");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一件战衣。
");
	set("makeinfo", "[1;31m
财迷(money)[1;31m 出品
[2;37;0m");
	set("value", 35760000);
	set("point", 1783);
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
	set("armor_prop/research_effect", 6);
	set("armor_prop/avoid_die", 2.500000);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
