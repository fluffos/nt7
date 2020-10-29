// ITEM Made by player(雪山飞龙:kimi) /data/item/k/kimi-yjcuff.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Feb 11 22:15:35 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m饮中[1;35m八仙[1;37m歌[2;37;0m", ({ "yjcuff" }));
	set_weight(4500);
	set("item_make", 1);
	set("unit", "双");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一双铁掌。
[1;32m饮如长鲸吸百川，挥毫落纸如云烟[2;37;0m
");
	set("makeinfo", "[1;31m
雪山飞龙(kimi)[1;31m 出品
[2;37;0m");
	set("value", 35080000);
	set("point", 1749);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 3);
	set("wear_msg", "[1;33m饮如[1;36m长鲸[1;37m[5m吸百川[2;37;0m\n");
	set("remove_msg", "[1;32m挥毫[1;37m落纸[1;36m[5m如云烟[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);
	set("armor_prop/research_effect", 3);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
