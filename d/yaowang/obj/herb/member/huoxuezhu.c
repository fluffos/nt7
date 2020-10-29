#include "herb.h"

void create()
{
        set_name(HIB "活血珠" NOR, ({ "huoxuezhu", "Pleione bulbocodioides", "herb_hxzhu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "兰科植物独蒜兰(Pleione bulbocodioides)的假鳞茎。因其假鳞茎底部圆形似珠，具舒筋活血功效，故得此名。\n" NOR);
                set("base_unit", "根");
                set("base_value", 30000);
                set("base_weight", 100);
        }
        setup();
}

