// ITEM Made by player(肯克哈洛:haluo) /data/item/h/haluo-ggg.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Jan  7 21:34:31 2019
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m事了[1;34m拂衣[1;35m去[2;37;0m", ({ "ggg" }));
	set_weight(15000);
	set("item_make", 1);
	set("unit", "张");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一张护甲。
");
	set("makeinfo", "[1;31m
肯克哈洛(haluo)[1;31m 出品
[2;37;0m");
	set("value", 34300000);
	set("point", 1368);
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
