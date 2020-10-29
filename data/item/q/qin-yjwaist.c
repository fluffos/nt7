// ITEM Made by player(秦云:qin) /data/item/q/qin-yjwaist.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jun 26 13:30:41 2019
#include <ansi.h>
#include <armor.h>

inherit WAIST;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m去留[1;35m肝胆[1;37m两昆仑[2;37;0m", ({ "yjwaist" }));
	set_weight(8000);
	set("item_make", 1);
	set("unit", "条");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一条腰带。
[1;32m我自横刀向天笑，去留肝胆两昆仑。[2;37;0m
");
	set("makeinfo", "[1;31m
秦云(qin)[1;31m 出品
[2;37;0m");
	set("value", 34900000);
	set("point", 696);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 3);
	set("wear_msg", "[1;33m我自[1;36m横刀[1;37m[5m向天笑[2;37;0m\n");
	set("remove_msg", "[1;32m去留[1;37m肝胆[1;36m[5m两昆仑[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/research_effect", 3);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
