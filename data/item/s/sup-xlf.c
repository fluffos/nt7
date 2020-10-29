// ITEM Made by player(辅助:sup) /data/item/s/sup-xlf.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Feb 13 00:20:43 2019
#include <ansi.h>
#include <weapon.h>

inherit THROWING;
inherit F_ITEMMAKE;

void create()
{
	set_name("小李飞[2;37;0m", ({ "xlf" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "把");
	set("long", "这是由[36m玄铁[2;37;0m炼制而成的一把暗器。
");
	set("makeinfo", "[1;31m
辅助(sup)[1;31m 出品
[2;37;0m");
	set("value", 1500000);
	set("base_weight", 90);
	set("base_unit", "枚");
	set("base_value", 1);
	set("point", 239);
	set("max_consistence", 100);
	set("material", "steel");
	set("material_file", "/d/item/obj/xuantie");
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
