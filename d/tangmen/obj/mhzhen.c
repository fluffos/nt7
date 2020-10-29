//mhzhen.c

#include <weapon.h>
#include <ansi.h>
inherit THROWING;
void create()
{
        set_name("梅花针", ({ "meihua zhen", "zhen" }) );
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "把");
                set("value", 10000);
                set("base_unit", "根");
                set("base_weight", 100);
                set("base_value", 200);
                set("material", "steel");
                set("long", "一根细若牛毛的针。\n");
                                
        }
       set_amount(50);
       init_throwing(50);
       setup();
}