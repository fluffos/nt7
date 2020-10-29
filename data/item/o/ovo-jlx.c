// ITEM Made by player(小球球:ovo) /data/item/o/ovo-jlx.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Jun 15 19:22:13 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[33m精力铁掌[2;37;0m", ({ "jlx" }));
	set_weight(450);
	set("item_make", 1);
	set("unit", "双");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一双铁掌。
");
	set("makeinfo", "[1;31m
小球球(ovo)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 1500);
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
	set("armor_prop/max_jingli", 4500);
	set("armor_prop/study_effect", 3);
	set("armor_prop/double_damage", 2.000000);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
