#include <ansi.h>
inherit TASK;
void create()
{
    set_name(BLU"武当录"NOR, ({ "wudanglu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "长勤武当录。\n");
          } 
    set("owner", "宋青书");
        setup();
}  
