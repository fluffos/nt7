// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(HIR"恶人首级"NOR, ({ "head" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", NOR + WHT "这是一枚在杏子林里砍下的四大恶人的首级。\n" NOR);
                set("base_unit", "枚");
                set("base_value", 1000);
                set("base_weight", 300);
                set("unit", "堆");
        }
        //set("maze_item", 1);
        //set("no_get", 1);
        //set("no_put", 1);
        //set("no_give", 1); //可以让大米去做本任务, ../的beggar.c里限制了可完成的主id等级
        set("no_sell", "这可是血淋淋的人头啊...\n");
        set("no_put", "这可是血淋淋的人头啊...\n");//不能放进乾坤袋，方便别人可以抢劫
                set("set_data", 1); //下线不掉，因为杏子林深处可能无法走路去老乞丐，只能quit
                set("auto_load", 1); 
        set("xzz/headlv", 1);
        setup();
        set_amount(1);
}




