// ITEM Made by player(石头:stone) /data/item/s/stone-sthw.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 22 13:15:39 2019
#include <ansi.h>
#include <armor.h>

inherit WRISTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("石头护腕[2;37;0m", ({ "sthw" }));
	set_weight(500);
	set("item_make", 1);
	set("unit", "对");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一对护腕。
");
	set("makeinfo", "[1;31m
石头(stone)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 172);
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
