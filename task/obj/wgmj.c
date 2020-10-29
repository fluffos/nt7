#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIG"武功秘笈"NOR, ({ "wugong miji" }) );
    set_weight(10);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "一本很厚的书，上面大大的写着武功秘笈四个大字。\n");
          }
    set("owner", "陈有德");
    setup();
}
