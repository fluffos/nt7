// ITEM Made by player(湖中:wash) /data/item/w/wash-xlfd.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Feb 17 19:02:47 2019
#include <ansi.h>
#include <weapon.h>

inherit THROWING;
inherit F_ITEMMAKE;

void create()
{
	set_name("小李飞刀[2;37;0m", ({ "xlfd" }));
	set_weight(300);
	set("item_make", 1);
	set("unit", "把");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一把暗器。
");
	set("makeinfo", "[1;31m
湖中(wash)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("base_weight", 3);
	set("base_unit", "枚");
	set("base_value", 1);
	set("point", 476);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 2);
	set("hand_msg", "[1;36m$N[1;36m一声清啸，握着一把[1;36m$n[1;36m。[2;37;0m\n");
	set("unhand_msg", "$N随手一抹，收起了$n。\n");
	if( !check_clone() ) return;
	restore();
	set_amount(100);
	init_throwing(apply_damage());

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
