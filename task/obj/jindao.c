#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIY "金刀" NOR,({ "jin dao" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "把");
                set("material", "gold");
                set("long", "这是一把金刀。\n");
        }
        set("owner", "郭靖");
        setup();
}

