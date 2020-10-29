
#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIW "铁索白袍" NOR, ({ "tiesuo baipao" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "件");
            set("material", "cloth");
            set("long", "这是一件铁索白袍。\n");
          }
    set("owner", "余沧海");
    setup();
}

