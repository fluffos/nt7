// ITEM Made by player(灭下:sky) /data/item/s/sky-ddd.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Jan 18 10:29:43 2019
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("[45;1m混沌钟[2;37;0m", ({ "ddd", "ddd" }));
	set_weight(15000);
	set("item_make", 1);
	set("unit", "张");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一张护甲。
");
	set("makeinfo", "[1;31m
灭下(sky)[1;31m 出品
[2;37;0m");
	set("value", 35420000);
	set("point", 1412);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 6);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/avoid_forget", 2.500000);
	set("armor_prop/research_effect", 9);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
