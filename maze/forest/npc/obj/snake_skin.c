#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name("蛇皮", ({ "she pi", "she", "pi" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", NOR + RED "巨蟒的皮革，质地坚韧，颇为罕见。\n" NOR);
                set("base_unit", "张");
                set("base_value", 4000);
                set("base_weight", 600);
        }
        set("maze_item", 1);
        setup();
        set_amount(1);
}