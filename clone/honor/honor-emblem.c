#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY "荣誉勋章" NOR, ({ "honor emblem", "emblem" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIY "一枚荣誉勋章，代表至高的荣誉。\n" NOR);
                set("unit", "枚");
                set("value", 500000);
        }
        setup();
}