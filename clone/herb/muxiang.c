#include "herb.h"

void create()
{
        set_name(YEL "木香" NOR, ({ "mu xiang" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("base_unit", "根");
                set("long", "终南山上的普通药材。\n");
                set("base_value", 4000);
                set("base_weight", 60);
                set("cure_s", 1);
                set("cure_d", 2);
                set("cure_n", 1);
        }
        setup();
}