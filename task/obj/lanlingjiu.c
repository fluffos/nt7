
#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIW "兰陵酒" NOR, ({ "lanling jiu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "壶");
            set("material", "stone");
            set("long", "这是一壶兰陵酒。\n");
          }
    set("owner", "李白");
    setup();
}

