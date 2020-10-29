// ITEM Made by player(雪山飞龙:kimi) /data/item/k/kimi-xblade.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Mar  8 09:52:20 2019
#include <ansi.h>
#include <weapon.h>

inherit BLADE;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;35m好好[1;37m学习[2;37;0m", ({ "xblade" }));
	set_weight(15000);
	set("item_make", 1);
	set("unit", "把");
	set("long", "这是由[1;37m寰宇天晶[2;37;0m炼制而成的一把刀。
[1;32m好好学习，天天向上[2;37;0m
");
	set("makeinfo", "[1;31m
雪山飞龙(kimi)[1;31m 出品
[2;37;0m");
	set("value", 4100000);
	set("point", 1000);
	set("max_consistence", 100);
	set("material", "tian jing");
	set("material_file", "/clone/goods/tianjing");
	set("quality_level", 2);
	set("wield_msg", "[1;33m为[1;36m人民[1;37m[5m服务[2;37;0m\n");
	set("unwield_msg", "[1;33m为[1;36m人民[1;37m[5m服务[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	init_blade(apply_damage());

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
