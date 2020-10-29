// bian.c 鞭

#include <weapon.h>
inherit WHIP;

void create()
{
        set_name("长鞭", ({ "chang bian", "bian","whip" }));
        set_weight(30);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", "这是一柄普通的长鞭，做工粗糙。\n");
                set("wield_msg", "$N「唰」的一声从腰后抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n别回腰后。\n");
        }
        init_whip(5);
        set("no_pk", 1);
	setup();
}