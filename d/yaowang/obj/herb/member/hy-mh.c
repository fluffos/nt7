#include "herb.h"

void create()
{
        set_name(HIC "梅花还阳" NOR, ({ "hy-mh", "Rhodobryum giganteum", "herb_hy_mh" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "真酵科植物暖地大叶藓(Rhodobryum giganteum)的全草。因其顶叶大.簇生如花苞状，形如梅花，故得此名。\n" NOR);
                set("base_unit", "颗");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

