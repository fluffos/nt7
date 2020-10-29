#include "herb.h"

void create()
{
        set_name(HIC "太阳还阳" NOR, ({ "hy-ty", "Polygonatum hookeri", "herb_hy_ty" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "百合科植物独花黄精(Polygonatum hookeri)的根茎。因其喜生长在向阳坡上.故得此名。\n" NOR);
                set("base_unit", "颗");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

