#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name("虎骨", ({"tiger bone"}) );
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", NOR + YEL "虎骨。\n" NOR);
                set("base_unit", "具");
                set("base_value", 8000);
                set("base_weight", 500);
        }
        set("maze_item", 1);
        setup();
        set_amount(1);
}