// ITEM Made by player(沐大哥:mudlet) /data/item/m/mudlet-suoyi.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu Jan 10 21:25:00 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("竹蓑衣[2;37;0m", ({ "suoyi" }));
	set_weight(20000);
	set("item_make", 1);
	set("unit", "件");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一件战衣。
一件竹子编的蓑衣[2;37;0m
");
	set("makeinfo", "[1;31m
沐大哥(mudlet)[1;31m 出品
[2;37;0m");
	set("value", 34160000);
	set("point", 1703);
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
