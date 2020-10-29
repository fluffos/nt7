// ITEM Made by player(上官天宇:cjl) /data/item/c/cjl-mypi.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 27 10:21:49 2019
#include <ansi.h>
#include <armor.h>

inherit SURCOAT;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31m血披风[2;37;0m", ({ "mypi" }));
	set_weight(10000);
	set("item_make", 1);
	set("unit", "件");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一件披风。
[1;31m血披风[2;37;0m
");
	set("makeinfo", "[1;31m
上官天宇(cjl)[1;31m 出品
[2;37;0m");
	set("value", 34920000);
	set("point", 870);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 6);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/reduce_damage", 2.500000);
	set("armor_prop/avoid_weak", 2.500000);
	set("armor_prop/research_effect", 6);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
