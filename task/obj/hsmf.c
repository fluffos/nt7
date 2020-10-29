#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIY"五香花生秘方"NOR, ({ "hsmfang" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "面");
            set("material", "paper");
            set("long", "五香花生秘方。\n");
          }
    set("owner", "阿庆嫂");
    setup();
}
