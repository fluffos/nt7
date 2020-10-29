// ITEM Made by player(秦云:qin) /data/item/q/qin-yjhead.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jun 26 13:40:56 2019
#include <ansi.h>
#include <armor.h>

inherit HEAD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m星垂[1;35m平野[1;37m阔[2;37;0m", ({ "yjhead" }));
	set_weight(7500);
	set("item_make", 1);
	set("unit", "顶");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一顶头盔。
[1;32m星垂平野阔，月涌大江流。[2;37;0m
");
	set("makeinfo", "[1;31m
秦云(qin)[1;31m 出品
[2;37;0m");
	set("value", 34500000);
	set("point", 860);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 3);
	set("wear_msg", "[1;33m星垂[1;36m平野[1;37m[5m阔[2;37;0m\n");
	set("remove_msg", "[1;32m月涌[1;37m大江[1;36m[5m流[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/research_effect", 3);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
