// liyu.c 糖醋鲤鱼

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIY "糖醋鲤鱼" NOR, ({"tangcu liyu", "liyu"}));
        set_weight(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一盘外焦里嫩，酸甜适口的糖醋鲤鱼。\n");
                set("unit", "盘");
                set("value", 250);
                set("food_remaining", 3);
                set("food_supply", 30);
        }
}