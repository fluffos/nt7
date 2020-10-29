// dafu.c 大斧

#include <weapon.h>
inherit AXE;

void create()
{
        set_name("大斧", ({ "dafu","fu" }));
        set_weight(10000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", "这是一柄大斧头。\n");
                set("value", 5000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回腰间。\n");
        }
      init_axe(20);
        setup();
}