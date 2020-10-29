// ITEM Made by player(糙汉:run) /data/item/r/run-wrists.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Feb  1 15:47:33 2019
#include <ansi.h>
#include <armor.h>

inherit WRISTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("护腕[2;37;0m", ({ "wrists" }));
	set_weight(500);
	set("item_make", 1);
	set("unit", "对");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一对护腕。
牛叉的护腕[2;37;0m
");
	set("makeinfo", "[1;31m
糙汉(run)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 375);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 6);
	set("wear_msg", "护腕戴上来了[2;37;0m\n");
	set("remove_msg", "护腕摘下去了[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/derive_effect", 3);
	set("armor_prop/dp_power", 1.500000);
	set("armor_prop/research_effect", 6);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
