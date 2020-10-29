//Cracked by Kafei
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("炒白菜", ({"chao baicai", "baicai"}));
        set_weight(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一碗喷香的炒白菜。\n");
                set("unit", "碗");
                set("value", 50);
                set("food_remaining", 1);
                set("food_supply", 15);
        }
}