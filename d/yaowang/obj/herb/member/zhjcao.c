#include "herb.h"

void create()
{
        set_name(GRN "转筋草" NOR, ({ "zhuanjin cao", "Pachysandra terminalis", "herb_zhjcao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "黄杨科植物顶花板凳果(又称富贵草)(Pachysandra terminalis)的带根全草。因其有舒筋活络功效，故得此名。\n" NOR);
                set("base_unit", "株");
                set("base_value", 60000);
                set("base_weight", 100);
        }
        setup();
}

