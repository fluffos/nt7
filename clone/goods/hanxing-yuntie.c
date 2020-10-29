#include <ansi.h>

inherit ITEM;
int is_forging_ob() { return 1; }

void create()
{
        set_name(HIB "寒星陨铁" NOR, ({"hanxing yuntie", "hanxing", "yuntie"}));
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", sort_msg(HIM "从太空掉落下来的一种寒星陨铁。"
                                         "似乎包容着不为人知的力量，但却感觉"
                                         "不到一点能量。\n" NOR));
                set("unit", "块");
                set("value", 20000000);
                set("item_origin", 1);
                set("material_attrib", "hanxing yuntie");
                set("material_name", HIM "寒星陨铁" NOR);
                set("can_make", "all");
                set("power_point", 200);
        }
}
