inherit TASK;
#include <ansi.h>
void create()
{
    set_name( HIM"客户定单" NOR, ({ "dingdan" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "张");
            set("material", "paper");
            set("long", "一张详细的定单，记载着丽春院的预定情况。\n");
        }
    set("owner", "韦春芳");
    setup(); 
}
