// ITEM Made by player(小球球:ovo) /data/item/o/ovo-nlg.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu Apr  4 20:41:25 2019
#include <ansi.h>
#include <armor.h>

inherit HEAD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;35m内内头盔[2;37;0m", ({ "nlg" }));
	set_weight(7500);
	set("item_make", 1);
	set("unit", "顶");
	set("long", "这是由[1;37m寰宇天晶[2;37;0m炼制而成的一顶头盔。
");
	set("makeinfo", "[1;31m
小球球(ovo)[1;31m 出品
[2;37;0m");
	set("value", 4100000);
	set("point", 283);
	set("max_consistence", 100);
	set("material", "tian jing");
	set("material_file", "/clone/goods/tianjing");
	set("quality_level", 4);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/defense", 20);
	set("armor_prop/max_neili", 8000);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
