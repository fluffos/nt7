
#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIW "藏宝图" NOR, ({ "cangbao tu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "张");
            set("material", "paper");
            set("long", "这是一张藏宝图。\n");
          }
    set("owner", "凌退思");
    setup();
}

