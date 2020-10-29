#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name("蛇蛋", ({"snake egg"}) );
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", NOR + WHT "蛇蛋。\n" NOR);
                set("base_unit", "个");
                set("base_value", 20000);
                set("base_weight", 600);
                set("no_give", 1);
        }
        set("maze_item", 1);
        setup();
        set_amount(1);
}