// ITEM Made by player(小球球:ovo) /data/item/o/ovo-yjg.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Apr  9 19:44:29 2019
#include <ansi.h>
#include <armor.h>

inherit HEAD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;34m烟酒头盔[2;37;0m", ({ "yjg" }));
	set_weight(7500);
	set("item_make", 1);
	set("unit", "顶");
	set("long", "这是由[1;37m寰宇天晶[2;37;0m炼制而成的一顶头盔。
");
	set("makeinfo", "[1;31m
小球球(ovo)[1;31m 出品
[2;37;0m");
	set("value", 4100000);
	set("point", 223);
	set("max_consistence", 100);
	set("material", "tian jing");
	set("material_file", "/clone/goods/tianjing");
	set("quality_level", 4);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/max_neili", 8000);
	set("armor_prop/research_effect", 2);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
