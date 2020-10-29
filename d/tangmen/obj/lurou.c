// lurou.c 野鹿肉

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("鹿肉", ({"lu rou", "rou"}));
        set_weight(400);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一大块鲜血淋漓的野鹿肉，很补的。\n");
                set("unit", "块");
                set("value", 300);
                set("food_remaining", 5);
                set("food_supply", 60);
        }
}