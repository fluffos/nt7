// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
//商城物品，每轮闯关限制使用
#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
                set_name(YEL"飞刀"HIC"灵符"NOR, ({"fly knife", "knife", "fei dao"}) ); 
                /*if (clonep())
                        set_default_object(__FILE__);
                else*/ {
                        set("long", NOR + WHT "这是一支杨小邪的飞刀，薄得近乎透明，上面还有一些乱七八糟的篆文，在灵感塔上可以使用它(use knife)。\n" NOR);
                        set("base_unit", "支");
                        set("base_value", 1000);
                        set("base_weight", 600);
                        set("unit", "叠");
                }
                set("set_data", 1); //下线不掉
                set("auto_load", 1); 
                setup();
                set_amount(3);
}




