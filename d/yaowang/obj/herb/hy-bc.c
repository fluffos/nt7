#include "herb.h"

void create()
{
        set_name(HIC "八宝" NOR, ({ "hy-bc", "Sedum erythrostictum", "herb_hy_bc" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "景天科植物八宝(又称景天)(Sedum erythrostictum)的全草。因其叶形如包菜叶，又称包菜还阳。\n" NOR);
                set("base_unit", "颗");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}