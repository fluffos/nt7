// ITEM Made by player(雪山飞龙:kimi) /data/item/k/kimi-yjarmor.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Feb 10 00:39:32 2019
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m张旭[1;35m三杯[1;37m草圣传[2;37;0m", ({ "yjarmor" }));
	set_weight(15000);
	set("item_make", 1);
	set("unit", "张");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一张护甲。
[1;32m张旭三杯草圣传，脱帽露顶王公前，挥毫落纸如云烟。[2;37;0m
");
	set("makeinfo", "[1;31m
雪山飞龙(kimi)[1;31m 出品
[2;37;0m");
	set("value", 34800000);
	set("point", 1388);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 3);
	set("wear_msg", "[1;33m挥毫[1;36m落纸[1;37m[5m如云烟[2;37;0m\n");
	set("remove_msg", "[1;32m脱帽[1;37m露顶[1;36m[5m王公前[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/research_effect", 3);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
