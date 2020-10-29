
#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIR "血红花儿" NOR, ({ "blood flower" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "朵");
            set("material", "wood");
            set("long", "这是一朵血红花儿。\n");
          }
    set("owner", "沈芝毓");
    setup();
}

