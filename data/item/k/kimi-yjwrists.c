// ITEM Made by player(雪山飞龙:kimi) /data/item/k/kimi-yjwrists.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Feb 10 00:13:35 2019
#include <ansi.h>
#include <armor.h>

inherit WRISTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m左相[1;35m日兴[1;37m费万钱[2;37;0m", ({ "yjwrists" }));
	set_weight(5000);
	set("item_make", 1);
	set("unit", "对");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一对护腕。
[1;32m左相日兴费万钱，饮如长鲸吸百川，衔杯乐圣称世贤[2;37;0m
");
	set("makeinfo", "[1;31m
雪山飞龙(kimi)[1;31m 出品
[2;37;0m");
	set("value", 35420000);
	set("point", 441);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 4);
	set("wear_msg", "[1;33m饮如[1;36m长鲸[1;37m[5m吸百川[2;37;0m\n");
	set("remove_msg", "[1;32m衔杯[1;37m乐圣[1;36m[5m称世贤[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/derive_times", 10);
	set("armor_prop/research_effect", 2);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
