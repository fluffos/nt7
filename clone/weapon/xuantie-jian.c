#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(NOR + WHT "玄铁重剑" NOR, ({ "xuantie jian", "xuantie", "jian" }));
        set_weight(5000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", "这是一柄天山玄铁铸造的大剑，入手沉重无比，剑刃却并不见得锋利。\n");
                set("value", 2000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
        }
        init_sword(500);
        setup();
}