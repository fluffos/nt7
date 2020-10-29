// ITEM Made by player(渡玩:alp) /data/item/a/alp-dzb.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Feb 18 10:55:21 2019
#include <ansi.h>
#include <weapon.h>

inherit STAFF;
inherit F_ITEMMAKE;

void create()
{
	set_name("大丈夫[2;37;0m", ({ "dzb" }));
	set_weight(1500);
	set("item_make", 1);
	set("unit", "根");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一根杖。
");
	set("makeinfo", "[1;31m
渡玩(alp)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 1377);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 2);
	set("wield_msg", "[1;36m$N[1;36m一声清啸，抖出一根[1;36m$n[1;36m。[2;37;0m\n");
	set("unwield_msg", "$N随手一抹，收起了$n。\n");
	if( !check_clone() ) return;
	restore();
	init_staff(apply_damage());

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
