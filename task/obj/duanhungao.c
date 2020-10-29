
#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIC "断魂膏" NOR, ({ "duanhun gao" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "贴");
            set("material", "wood");
            set("long", "这是一贴断魂膏。\n");
          }
    set("owner", "阎基");
    setup();
}

