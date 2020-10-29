#include "herb.h"

void create()
{
        set_name(HIC "金丝还阳" NOR, ({ "hy-js", "herb_hy_js" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "金发茧科植物高山金发藓的全草。因其植物体早黄棕色，形如金丝，故得此名。。\n" NOR);
                set("base_unit", "颗");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

