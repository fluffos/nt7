inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIG "龙女之泪" NOR, ({"longnv zhilei", "longnv", "zhilei" }));
        set_weight(900);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIG "传说龙女之泪乃东海小龙女心泪凝而成，拥有着令世人无法抗拒的力量。\n" NOR);
                set("unit", "块");
                set("value", 5000);
                set("enchase/name", "龙女之泪");
                set("enchase/point", 200);
                  set("enchase/type", "all");
                set("enchase/cur_firm", 90);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}
