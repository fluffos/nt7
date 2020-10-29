// longsword.c 长剑

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("安南短剑", ({ "duanjian", "jian" }));
        set_weight(5000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", "这是一柄普通的精钢剑，一般的剑客都配带此剑。\n");
                set("value", 1500);
                set("life",20);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
        }
        init_sword(500);
        setup();
}