// ITEM Made by player(唐弹:jobc) /data/item/j/jobc-smz.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Feb  1 21:12:47 2019
#include <ansi.h>
#include <armor.h>

inherit FINGER;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;37m小指[2;37;0m", ({ "smz" }));
	set_weight(350);
	set("item_make", 1);
	set("unit", "套");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一套指套。
");
	set("makeinfo", "[1;31m
唐弹(jobc)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 571);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 5);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);
	set("armor_prop/avoid_dodge", 1.500000);
	set("armor_prop/leech_qi", 2.000000);
	set("armor_prop/attack", 30);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
