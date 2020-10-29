#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIR "科举考题" NOR,({ "keju kaoti" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "个");
                set("material", "paper");
                set("long", "这是一个科举考题。\n");
        }
        set("owner", "考官");
        setup();
}

