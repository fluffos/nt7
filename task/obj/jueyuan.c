#include <ansi.h>
inherit TASK;
void create()
{
    set_name(WHT"铁水桶"NOR, ({ "tie shuitong", "shui tong" }) );
    set_weight(100);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "个");
            set("material", "iron");
            set("long", "一个普通的铁水桶，桶身刻着“少林寺”的字样，看来是少林寺之物。\n");
          }
    set("owner", "觉远");
    setup();
}
