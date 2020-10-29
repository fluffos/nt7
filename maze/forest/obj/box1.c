#include <ansi.h>
inherit BAOXIANG_ITEM;

void create()
{
        set_name(HIC"宝箱"NOR, ({"box"}) );
        set_weight(300);
        set_max_encumbrance(80000000);
        set("unit", "些");
        set("long", "一个散发着神秘光芒的宝箱，或许可以打开(open)它。\n");
        set("closed", 1);
        set("no_get", 1);
        set("base_value", 200);
        set("base_unit", "个");
        set("BAOXIANG_LIST",([ 
                "/clone/money/gold":200,   //物品文件名:概率 
                "/clone/money/silver":300,   //物品文件名:概率
                "/clone/money/coin":500,   //物品文件名:概率
        ]));
 
        set_amount(1);
} 

void init()
{
        add_action("do_open", "open");
}