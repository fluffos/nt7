// ITEM Made by player(雪山飞龙:kimi) /data/item/k/kimi-ysurcoat.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Feb 10 00:46:35 2019
#include <ansi.h>
#include <armor.h>

inherit SURCOAT;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m焦遂[1;35m五斗[1;37m方卓然[2;37;0m", ({ "ysurcoat" }));
	set_weight(10000);
	set("item_make", 1);
	set("unit", "件");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一件披风。
[1;32m焦遂五斗方卓然，高谈雄辨惊四筵。[2;37;0m
");
	set("makeinfo", "[1;31m
雪山飞龙(kimi)[1;31m 出品
[2;37;0m");
	set("value", 35420000);
	set("point", 883);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 3);
	set("wear_msg", "[1;33m焦遂[1;36m五斗[1;37m[5m方卓然[2;37;0m\n");
	set("remove_msg", "[1;32m高谈[1;37m雄辨[1;36m[5m惊四筵[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/research_effect", 3);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
