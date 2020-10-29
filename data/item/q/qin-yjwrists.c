// ITEM Made by player(秦云:qin) /data/item/q/qin-yjwrists.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jun 26 13:20:35 2019
#include <ansi.h>
#include <armor.h>

inherit WRISTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m西北望[1;35m射[1;37m天狼[2;37;0m", ({ "yjwrists" }));
	set_weight(5000);
	set("item_make", 1);
	set("unit", "对");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一对护腕。
[1;32m会挽雕弓如满月，西北望，射天狼。[2;37;0m
");
	set("makeinfo", "[1;31m
秦云(qin)[1;31m 出品
[2;37;0m");
	set("value", 35160000);
	set("point", 438);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 5);
	set("wear_msg", "[1;33m会挽[1;36m雕弓[1;37m[5m如满月[2;37;0m\n");
	set("remove_msg", "[1;32m西北[1;37m望[1;36m[5m射天狼[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/learn_times", 15);
	set("armor_prop/avoid_poison", 1.500000);
	set("armor_prop/research_effect", 3);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
