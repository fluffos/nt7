// ITEM Made by player(输出:adc) /data/item/a/adc-xcd.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Feb  4 21:04:17 2019
#include <ansi.h>
#include <weapon.h>

inherit BLADE;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;34m小菜刀[2;37;0m", ({ "xcd" }));
	set_weight(1500);
	set("item_make", 1);
	set("unit", "把");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一把刀。
");
	set("makeinfo", "[1;31m
输出(adc)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 534);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 2);
	set("wield_msg", "[1;36m$N[1;36m一声清啸，抖出一把[1;36m$n[1;36m。[2;37;0m\n");
	set("unwield_msg", "$N随手一抹，收起了$n。\n");
	if( !check_clone() ) return;
	restore();
	init_blade(apply_damage());

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
