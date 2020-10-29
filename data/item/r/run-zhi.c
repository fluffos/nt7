// ITEM Made by player(糙汉:run) /data/item/r/run-zhi.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Jan 18 18:56:40 2019
#include <ansi.h>
#include <armor.h>

inherit FINGER;
inherit F_ITEMMAKE;

void create()
{
	set_name("金手指[2;37;0m", ({ "zhi" }));
	set_weight(3500);
	set("item_make", 1);
	set("unit", "套");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一套指套。
传说中具有神奇功能的手指[2;37;0m
");
	set("makeinfo", "[1;31m
糙汉(run)[1;31m 出品
[2;37;0m");
	set("value", 35080000);
	set("point", 1749);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 2);
	set("wear_msg", "金手指一出，天下寂静。[2;37;0m\n");
	set("remove_msg", "金手指消失了。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
