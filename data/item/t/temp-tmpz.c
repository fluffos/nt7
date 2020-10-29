// ITEM Made by player(渡腾:temp) /data/item/t/temp-tmpz.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu Apr 18 20:22:55 2019
#include <ansi.h>
#include <weapon.h>

inherit WHIP;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;35m巨齿鞭[2;37;0m", ({ "tmpz" }));
	set_weight(1500);
	set("item_make", 1);
	set("unit", "根");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一根鞭。
");
	set("makeinfo", "[1;31m
渡腾(temp)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 300);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 3);
	set("wield_msg", "[1;36m$N[1;36m一声清啸，抖出一根[1;36m$n[1;36m。[2;37;0m\n");
	set("unwield_msg", "$N随手一抹，收起了$n。\n");
	if( !check_clone() ) return;
	restore();
	init_whip(apply_damage());
	set("weapon_prop/practice_times", 10);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
