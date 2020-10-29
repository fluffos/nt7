#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "无名之物加强型" NOR, ({"no name2", "no", "name2"}));
        set_weight(10000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", sort_msg(HIM "非金非玉非石非木无名之物，看似平凡"
                                         "但又似不平凡，忽隐忽现，忽明忽暗。"
                                         "似乎包容着不为人知的力量，但却感觉"
                                         "不到一点能量。\n" NOR));
                set("unit", "块");
                set("value", 20000000);
                set("item_origin", 1);
                set("material_attrib", "no name");
                set("material_name", HIM "无名之物" NOR);
                set("can_make", "all");
                set("power_point", 1700+random(101));
        }
}

