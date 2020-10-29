#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIC"绝命腿法"NOR, ({ "jueming tuifa" }) );
    set_weight(10);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "一本关于腿法的无功秘笈。\n");
          }
    set("owner", "黎生");
    setup();
}
