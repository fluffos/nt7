// ITEM Made by player(糙汉:run) /data/item/r/run-hushou.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Jan 18 21:22:59 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("金护手[2;37;0m", ({ "hushou" }));
	set_weight(4000);
	set("item_make", 1);
	set("unit", "双");
	set("long", "这是由[1;37m寰宇天晶[2;37;0m炼制而成的一双护手。
金护手具有神奇的力量，能加快研究速度九倍。[2;37;0m
");
	set("makeinfo", "[1;31m
糙汉(run)[1;31m 出品
[2;37;0m");
	set("value", 4100000);
	set("point", 586);
	set("max_consistence", 100);
	set("material", "tian jing");
	set("material_file", "/clone/goods/tianjing");
	set("quality_level", 2);
	set("wear_msg", "金护手一出，天下寂静。[2;37;0m\n");
	set("remove_msg", "金护手消失了。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
