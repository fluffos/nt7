#include "herb.h"

void create()
{
        set_name(HIC "猪耳朵" NOR, ({ "hy-zhu", "Senecio goodianux", "herb_hy_zhu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "菊科植物单头千里光(Senecio goodianux)的全草。因其叶形如猪耳朵，故得此名。\n" NOR);
                set("base_unit", "颗");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

