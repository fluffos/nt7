inherit ITEM;
inherit F_FOOD;
#include <ansi.h>

void create()
{
        set_name(HIC "酱牛肉" NOR, ({"rou"}));
        set_weight(50);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "盘");
                set("long", "这是一盘酱制了三个月的熟牛肉，是下酒的好菜。\n");
                set("value", 0);
                set("food_remaining", 5);
                set("food_supply", 20);
        }
        setup();
}