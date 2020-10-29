#include <ansi.h>
inherit TASK;
void create()
{
    set_name( CYN "衣样" NOR, ({ "yi yang" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "件");
            set("material", "cloth");
            set("long", "一件用来做衣服的衣样，上面还有一股淡淡的清香。\n");
          }
    set("owner", "曾柔");
    setup();
}
