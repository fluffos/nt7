// ITEM Made by player(单丁:sana) /data/item/s/sana-xba.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Feb 15 12:29:44 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("信标[2;37;0m", ({ "xba" }));
	set_weight(2400);
	set("item_make", 1);
	set("unit", "双");
	set("long", "这是由[1;35m神铁[2;37;0m炼制而成的一双护手。
");
	set("makeinfo", "[1;31m
单丁(sana)[1;31m 出品
[2;37;0m");
	set("value", 2100000);
	set("point", 226);
	set("max_consistence", 100);
	set("material", "magic stone");
	set("material_file", "/d/item/obj/butian");
	set("quality_level", 2);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
