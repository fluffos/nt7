// ITEM Made by player(涂鸦人生:mlove) /data/item/m/mlove-mlh.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Jan  7 17:54:14 2019
#include <ansi.h>
#include <weapon.h>

inherit STAFF;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31m朝天[1;33m一[1;35m棍[2;37;0m", ({ "mlh" }));
	set_weight(15000);
	set("item_make", 1);
	set("unit", "根");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一根杖。
");
	set("makeinfo", "[1;31m
涂鸦人生(mlove)[1;31m 出品
[2;37;0m");
	set("value", 35900000);
	set("point", 1790);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 2);
	set("wield_msg", "[1;36m$N[1;36m一声清啸，抖出一根[1;36m$n[1;36m。[2;37;0m\n");
	set("unwield_msg", "$N随手一抹，收起了$n。\n");
	if( !check_clone() ) return;
	restore();
	init_staff(apply_damage());

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
