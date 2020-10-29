#include "herb.h"

void create()
{
        set_name(YEL "山菊" NOR, ({ "shan ju" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("base_unit", "根");
                set("long", "终南山上的山菊，药材，清火。\n");
                set("base_value", 200);
                set("base_weight", 50);
                set("cure_s", 1);
                set("cure_d", 3);
                set("cure_n", 1);
        }
        setup();
}