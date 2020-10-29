//Cracked by Kafei
// zhangrou.c 獐肉

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("獐肉", ({"zhang rou", "zhang"}));
        set_weight(300);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一块鲜血淋漓的獐肉。\n");
                set("unit", "块");
                set("value", 100);
                set("food_remaining", 4);
                set("food_supply", 50);
        }
}