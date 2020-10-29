// ITEM Made by player(雪山飞龙:kimi) /data/item/k/kimi-yjboots.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Feb 10 00:32:43 2019
#include <ansi.h>
#include <armor.h>

inherit BOOTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m苏晋[1;35m长斋[1;37m绣佛前[2;37;0m", ({ "yjboots" }));
	set_weight(6000);
	set("item_make", 1);
	set("unit", "双");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一双靴子。
[1;32m苏晋长斋绣佛前，醉中往往爱逃禅[2;37;0m
");
	set("makeinfo", "[1;31m
雪山飞龙(kimi)[1;31m 出品
[2;37;0m");
	set("value", 35360000);
	set("point", 705);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 3);
	set("wear_msg", "[1;33m苏晋[1;36m长斋[1;37m[5m绣佛前[2;37;0m\n");
	set("remove_msg", "[1;32m醉中[1;37m往往[1;36m[5m爱逃禅[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/research_effect", 3);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
