// ITEM Made by player(空煤:mud) /data/item/m/mud-mudf.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Apr 17 00:28:04 2019
#include <ansi.h>
#include <armor.h>

inherit WAIST;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[34m虚影腰带[2;37;0m", ({ "mudf" }));
	set_weight(800);
	set("item_make", 1);
	set("unit", "条");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一条腰带。
");
	set("makeinfo", "[1;31m
空煤(mud)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 600);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 4);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/dp_power", 1.200000);
	set("armor_prop/parry", 20);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
