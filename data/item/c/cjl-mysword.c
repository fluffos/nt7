// ITEM Made by player(上官天宇:cjl) /data/item/c/cjl-mysword.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 29 11:32:12 2019
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m金虹[2;37;0m", ({ "mysword" }));
	set_weight(15000);
	set("item_make", 1);
	set("unit", "柄");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一柄剑。
[1;33m金虹[2;37;0m
");
	set("makeinfo", "[1;31m
上官天宇(cjl)[1;31m 出品
[2;37;0m");
	set("value", 34140000);
	set("point", 1702);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 6);
	set("wield_msg", "[1;36m$N[1;36m一声清啸，抖出一柄[1;36m$n[1;36m。[2;37;0m\n");
	set("unwield_msg", "$N随手一抹，收起了$n。\n");
	if( !check_clone() ) return;
	restore();
	init_sword(apply_damage());
	set("weapon_prop/fatal_blow", 2.000000);
	set("weapon_prop/add_weak", 2.500000);
	set("weapon_prop/practice_effect", 6);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
