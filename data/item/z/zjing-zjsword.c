// ITEM Made by player(马三:zjing) /data/item/z/zjing-zjsword.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan 16 13:53:32 2019
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m汽车人[1;32m千斤顶[2;37;0m", ({ "zjsword" }));
	set_weight(15000);
	set("item_make", 1);
	set("unit", "柄");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一柄剑。
");
	set("makeinfo", "[1;31m
马三(zjing)[1;31m 出品
[2;37;0m");
	set("value", 34360000);
	set("point", 1713);
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
	set("weapon_prop/da_power", 2.000000);
	set("weapon_prop/add_damage", 2.500000);
	set("weapon_prop/research_effect", 3);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
