// ITEM Made by player(输出:adc) /data/item/a/adc-wdc.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Feb  5 17:58:37 2019
#include <ansi.h>
#include <weapon.h>

inherit HAMMER;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;36m王大锤[2;37;0m", ({ "wdc" }));
	set_weight(3500);
	set("item_make", 1);
	set("unit", "把");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一把锤。
");
	set("makeinfo", "[1;31m
输出(adc)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 1098);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 2);
	set("wield_msg", "[1;36m$N[1;36m一声清啸，抖出一把[1;36m$n[1;36m。[2;37;0m\n");
	set("unwield_msg", "$N随手一抹，收起了$n。\n");
	if( !check_clone() ) return;
	restore();
	init_hammer(apply_damage());

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
