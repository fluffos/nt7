// ITEM Made by player(煤球:mud) /data/item/m/mud-muda.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Apr 14 15:09:22 2019
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[34m虚影剑[2;37;0m", ({ "muda" }));
	set_weight(1500);
	set("item_make", 1);
	set("unit", "柄");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一柄剑。
");
	set("makeinfo", "[1;31m
煤球(mud)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 1500);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 5);
	set("wield_msg", "[1;36m$N[1;36m一声清啸，抖出一柄[1;36m$n[1;36m。[2;37;0m\n");
	set("unwield_msg", "$N随手一抹，收起了$n。\n");
	if( !check_clone() ) return;
	restore();
	init_sword(apply_damage());
	set("weapon_prop/da_power", 1.500000);
	set("weapon_prop/leech_neili", 1.500000);
	set("weapon_prop/practice_times", 10);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
