// ITEM Made by player(小球球:ovo) /data/item/o/ovo-yja.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Apr 10 19:27:22 2019
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;34m烟酒剑[2;37;0m", ({ "yja" }));
	set_weight(1500);
	set("item_make", 1);
	set("unit", "柄");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一柄剑。
");
	set("makeinfo", "[1;31m
小球球(ovo)[1;31m 出品
[2;37;0m");
	set("value", 6100000);
	set("point", 671);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname");
	set("quality_level", 5);
	set("wield_msg", "[1;36m$N[1;36m一声清啸，抖出一柄[1;36m$n[1;36m。[2;37;0m\n");
	set("unwield_msg", "$N随手一抹，收起了$n。\n");
	if( !check_clone() ) return;
	restore();
	init_sword(apply_damage());
	set("weapon_prop/derive_effect", 2);
	set("weapon_prop/avoid_dodge", 1.200000);
	set("weapon_prop/research_effect", 2);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
