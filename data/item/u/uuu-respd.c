// ITEM Made by player(魔虎:uuu) /data/item/u/uuu-respd.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu May 16 21:35:47 2019
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;32m研绝护甲[2;37;0m", ({ "respd" }));
	set_weight(1500);
	set("item_make", 1);
	set("unit", "张");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一张护甲。
");
	set("makeinfo", "[1;31m
魔虎(uuu)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 1200);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 5);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/practice_effect", 6);
	set("armor_prop/avoid_blind", 1.500000);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
