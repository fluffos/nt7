#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("钢剑", ({ "gangjian", "jian","sword" }));
        set_weight(5000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", "这是一柄官兵用的钢剑。\n");
                set("value", 1500);
            set("super",2);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
        }
        init_sword(20,100,100);
        setup();
}