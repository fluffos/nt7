#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIM "素女经" NOR, ({ "sunvjing" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "一本素女经。\n");
          }
    set("owner", "欧阳克");
    setup();
}
