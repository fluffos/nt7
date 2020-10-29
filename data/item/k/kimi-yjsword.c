// ITEM Made by player(雪山飞龙:kimi) /data/item/k/kimi-yjsword.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Feb  9 23:00:03 2019
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m李白[1;35m一斗[1;37m诗百篇[2;37;0m", ({ "yjsword" }));
	set_weight(15000);
	set("item_make", 1);
	set("unit", "柄");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一柄剑。
李白一斗诗百篇，长安市上酒家眠。天子呼来不上船，自称臣是酒中仙。[2;37;0m
");
	set("makeinfo", "[1;31m
雪山飞龙(kimi)[1;31m 出品
[2;37;0m");
	set("value", 35340000);
	set("point", 1762);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 3);
	set("wield_msg", "李白一斗诗百篇，长安市上酒家眠[2;37;0m\n");
	set("unwield_msg", "天子呼来不上船，自称臣是酒中仙[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	init_sword(apply_damage());
	set("weapon_prop/research_effect", 3);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
