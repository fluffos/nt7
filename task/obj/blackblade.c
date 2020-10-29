
#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIK "漆黑的刀" NOR, ({ "black blade" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "把");
            set("material", "steel");
            set("long", "这是一把漆黑的刀。\n");
          }
    set("owner", "傅红雪");
    setup();
}

