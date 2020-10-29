// This program is a part of NITAN MudLIB 
// redl 2012/12/1 
//商城物品，每轮闯关限制使用，延长闯关时间30秒
#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
                set_name(HIC"塔灵"HIM"水晶"NOR, ({"tower crystal", "crystal", "tower"}) ); 
                /*if (clonep())
                        set_default_object(__FILE__);
                else*/ {
                        set("long", NOR + WHT "这是一块塔灵凝练出的水晶，蕴含着强大的时间之力。在灵感塔上可以使用它(use crystal)。\n" NOR);
                        set("base_unit", "块");
                        set("base_value", 1000);
                        set("base_weight", 600);
                        set("unit", "堆");
                }
                set("set_data", 1); //下线不掉
                set("auto_load", 1); 
                setup();
                set_amount(1);
}




