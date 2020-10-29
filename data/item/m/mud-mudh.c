// ITEM Made by player(煤球:mud) /data/item/m/mud-mudh.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Apr 14 12:31:33 2019
#include <ansi.h>
#include <armor.h>

inherit BOOTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[34m虚影靴子[2;37;0m", ({ "mudh" }));
	set_weight(600);
	set("item_make", 1);
	set("unit", "双");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一双靴子。
");
	set("makeinfo", "[1;31m
煤球(mud)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 600);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 5);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/max_qi", 3500);
	set("armor_prop/kar", 2);
	set("armor_prop/avoid_attack", 1.200000);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
