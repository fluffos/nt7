#include "herb.h"

void create()
{
        set_name(HIC "岩石还阳" NOR, ({ "hy-ys", "Chlamydoboea sinensis", "herb_hy_ys" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "苦苣苔科植物宽萼苣苔(Chlamydoboea sinensis)的全草。因其多生长在岩石夯，故得此名。\n" NOR);
                set("base_unit", "颗");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

