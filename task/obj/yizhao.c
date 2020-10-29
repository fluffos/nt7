#include <ansi.h>
inherit TASK;
void create()
{
    set_name( WHT "国姓爷遗诏" NOR, ({ "yi zhao" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "张");
            set("material", "paper");
            set("long", "果姓爷临死前写下的遗诏。\n");
          }
    set("owner", "郑克爽");
    setup();
}
