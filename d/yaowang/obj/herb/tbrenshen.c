#include "herb.h"

void create()
{
        set_name(HIW "太白人参" NOR, ({ "taibai renshen", "Pedicularis decora", "herb_tbrenshen" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "玄参科植物美观马先蒿(Pedicularis decora)的根茎。因其根形略似人参，且有类似人参的功效，太白山有产，故得此名。\n" NOR);
                set("base_unit", "株");
                set("base_value", 60000);
                set("base_weight", 100);
        }
        setup();
}